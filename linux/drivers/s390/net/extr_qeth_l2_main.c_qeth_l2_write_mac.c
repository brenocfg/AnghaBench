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
struct qeth_card {int dummy; } ;
typedef  enum qeth_ipa_cmds { ____Placeholder_qeth_ipa_cmds } qeth_ipa_cmds ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int EEXIST ; 
 int IPA_CMD_SETGMAC ; 
 int IPA_CMD_SETVMAC ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 int qeth_l2_send_setdelmac (struct qeth_card*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qeth_l2_write_mac(struct qeth_card *card, u8 *mac)
{
	enum qeth_ipa_cmds cmd = is_multicast_ether_addr(mac) ?
					IPA_CMD_SETGMAC : IPA_CMD_SETVMAC;
	int rc;

	QETH_CARD_TEXT(card, 2, "L2Wmac");
	rc = qeth_l2_send_setdelmac(card, mac, cmd);
	if (rc == -EEXIST)
		QETH_DBF_MESSAGE(2, "MAC already registered on device %x\n",
				 CARD_DEVID(card));
	else if (rc)
		QETH_DBF_MESSAGE(2, "Failed to register MAC on device %x: %d\n",
				 CARD_DEVID(card), rc);
	return rc;
}