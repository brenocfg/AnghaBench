#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct btmrvl_sdio_card {int /*<<< orphan*/  func; } ;
struct TYPE_2__ {struct btmrvl_sdio_card* card; } ;
struct btmrvl_private {TYPE_1__ btmrvl_dev; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BT_INFO (char*,char*) ; 
 int /*<<< orphan*/  btmrvl_sdio_wakeup_fw (struct btmrvl_private*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int sdio_f0_readb (int /*<<< orphan*/ ,unsigned int,int*) ; 
 int sdio_readb (int /*<<< orphan*/ ,unsigned int,int*) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void btmrvl_sdio_dump_regs(struct btmrvl_private *priv)
{
	struct btmrvl_sdio_card *card = priv->btmrvl_dev.card;
	int ret = 0;
	unsigned int reg, reg_start, reg_end;
	char buf[256], *ptr;
	u8 loop, func, data;
	int MAX_LOOP = 2;

	btmrvl_sdio_wakeup_fw(priv);
	sdio_claim_host(card->func);

	for (loop = 0; loop < MAX_LOOP; loop++) {
		memset(buf, 0, sizeof(buf));
		ptr = buf;

		if (loop == 0) {
			/* Read the registers of SDIO function0 */
			func = loop;
			reg_start = 0;
			reg_end = 9;
		} else {
			func = 2;
			reg_start = 0;
			reg_end = 0x09;
		}

		ptr += sprintf(ptr, "SDIO Func%d (%#x-%#x): ",
			       func, reg_start, reg_end);
		for (reg = reg_start; reg <= reg_end; reg++) {
			if (func == 0)
				data = sdio_f0_readb(card->func, reg, &ret);
			else
				data = sdio_readb(card->func, reg, &ret);

			if (!ret) {
				ptr += sprintf(ptr, "%02x ", data);
			} else {
				ptr += sprintf(ptr, "ERR");
				break;
			}
		}

		BT_INFO("%s", buf);
	}

	sdio_release_host(card->func);
}