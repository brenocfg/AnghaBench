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
 int IPA_CMD_DELGMAC ; 
 int IPA_CMD_DELVMAC ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 int qeth_l2_send_setdelmac (struct qeth_card*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qeth_l2_remove_mac(struct qeth_card *card, u8 *mac)
{
	enum qeth_ipa_cmds cmd = is_multicast_ether_addr(mac) ?
					IPA_CMD_DELGMAC : IPA_CMD_DELVMAC;
	int rc;

	QETH_CARD_TEXT(card, 2, "L2Rmac");
	rc = qeth_l2_send_setdelmac(card, mac, cmd);
	if (rc)
		QETH_DBF_MESSAGE(2, "Failed to delete MAC on device %u: %d\n",
				 CARD_DEVID(card), rc);
	return rc;
}