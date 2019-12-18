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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct lbs_private {int /*<<< orphan*/  dev; scalar_t__ card; } ;
struct if_cs_card {int dummy; } ;

/* Variables and functions */
 int IF_CS_BIT_COMMAND ; 
 int /*<<< orphan*/  IF_CS_CARD_STATUS ; 
 int /*<<< orphan*/  IF_CS_CMD ; 
 int /*<<< orphan*/  IF_CS_CMD_LEN ; 
 int /*<<< orphan*/  IF_CS_HOST_INT_CAUSE ; 
 int /*<<< orphan*/  IF_CS_HOST_STATUS ; 
 int /*<<< orphan*/  if_cs_disable_ints (struct if_cs_card*) ; 
 int /*<<< orphan*/  if_cs_enable_ints (struct if_cs_card*) ; 
 int if_cs_read16 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_write16 (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_cs_write16_rep (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_cs_write8 (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int if_cs_send_cmd(struct lbs_private *priv, u8 *buf, u16 nb)
{
	struct if_cs_card *card = (struct if_cs_card *)priv->card;
	int ret = -1;
	int loops = 0;

	if_cs_disable_ints(card);

	/* Is hardware ready? */
	while (1) {
		u16 status = if_cs_read16(card, IF_CS_CARD_STATUS);
		if (status & IF_CS_BIT_COMMAND)
			break;
		if (++loops > 100) {
			netdev_err(priv->dev, "card not ready for commands\n");
			goto done;
		}
		mdelay(1);
	}

	if_cs_write16(card, IF_CS_CMD_LEN, nb);

	if_cs_write16_rep(card, IF_CS_CMD, buf, nb / 2);
	/* Are we supposed to transfer an odd amount of bytes? */
	if (nb & 1)
		if_cs_write8(card, IF_CS_CMD, buf[nb-1]);

	/* "Assert the download over interrupt command in the Host
	 * status register" */
	if_cs_write16(card, IF_CS_HOST_STATUS, IF_CS_BIT_COMMAND);

	/* "Assert the download over interrupt command in the Card
	 * interrupt case register" */
	if_cs_write16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_COMMAND);
	ret = 0;

done:
	if_cs_enable_ints(card);
	return ret;
}