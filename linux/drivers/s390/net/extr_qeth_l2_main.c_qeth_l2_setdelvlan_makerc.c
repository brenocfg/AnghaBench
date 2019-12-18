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
typedef  int u16 ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int EPERM ; 
#define  IPA_RC_L2_DUP_VLAN_ID 132 
#define  IPA_RC_L2_INVALID_VLAN_ID 131 
#define  IPA_RC_L2_VLAN_ID_NOT_ALLOWED 130 
#define  IPA_RC_L2_VLAN_ID_NOT_FOUND 129 
#define  IPA_RC_SUCCESS 128 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 

__attribute__((used)) static int qeth_l2_setdelvlan_makerc(struct qeth_card *card, u16 retcode)
{
	if (retcode)
		QETH_CARD_TEXT_(card, 2, "err%04x", retcode);

	switch (retcode) {
	case IPA_RC_SUCCESS:
		return 0;
	case IPA_RC_L2_INVALID_VLAN_ID:
		return -EINVAL;
	case IPA_RC_L2_DUP_VLAN_ID:
		return -EEXIST;
	case IPA_RC_L2_VLAN_ID_NOT_FOUND:
		return -ENOENT;
	case IPA_RC_L2_VLAN_ID_NOT_ALLOWED:
		return -EPERM;
	default:
		return -EIO;
	}
}