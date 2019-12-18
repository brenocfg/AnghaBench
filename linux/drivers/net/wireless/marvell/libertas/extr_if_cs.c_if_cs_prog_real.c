#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct if_cs_card {int dummy; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENODEV ; 
 int IF_CS_BIT_COMMAND ; 
 int /*<<< orphan*/  IF_CS_CARD_STATUS ; 
 int /*<<< orphan*/  IF_CS_CMD ; 
 int /*<<< orphan*/  IF_CS_CMD_LEN ; 
 int /*<<< orphan*/  IF_CS_HOST_INT_CAUSE ; 
 int /*<<< orphan*/  IF_CS_HOST_STATUS ; 
 int /*<<< orphan*/  IF_CS_SCRATCH ; 
 int IF_CS_SQ_HELPER_OK ; 
 int /*<<< orphan*/  IF_CS_SQ_READ_LOW ; 
 int if_cs_poll_while_fw_download (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int if_cs_read16 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_write16 (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_cs_write16_rep (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_cs_write8 (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lbs_deb_cs (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int if_cs_prog_real(struct if_cs_card *card, const struct firmware *fw)
{
	int ret = 0;
	int retry = 0;
	int len = 0;
	int sent;

	lbs_deb_cs("fw size %td\n", fw->size);

	ret = if_cs_poll_while_fw_download(card, IF_CS_SQ_READ_LOW,
		IF_CS_SQ_HELPER_OK);
	if (ret < 0) {
		pr_err("helper firmware doesn't answer\n");
		goto done;
	}

	for (sent = 0; sent < fw->size; sent += len) {
		len = if_cs_read16(card, IF_CS_SQ_READ_LOW);
		if (len & 1) {
			retry++;
			pr_info("odd, need to retry this firmware block\n");
		} else {
			retry = 0;
		}

		if (retry > 20) {
			pr_err("could not download firmware\n");
			ret = -ENODEV;
			goto done;
		}
		if (retry) {
			sent -= len;
		}


		if_cs_write16(card, IF_CS_CMD_LEN, len);

		if_cs_write16_rep(card, IF_CS_CMD,
			&fw->data[sent],
			(len+1) >> 1);
		if_cs_write8(card, IF_CS_HOST_STATUS, IF_CS_BIT_COMMAND);
		if_cs_write16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_COMMAND);

		ret = if_cs_poll_while_fw_download(card, IF_CS_CARD_STATUS,
			IF_CS_BIT_COMMAND);
		if (ret < 0) {
			pr_err("can't download firmware at 0x%x\n", sent);
			goto done;
		}
	}

	ret = if_cs_poll_while_fw_download(card, IF_CS_SCRATCH, 0x5a);
	if (ret < 0)
		pr_err("firmware download failed\n");

done:
	return ret;
}