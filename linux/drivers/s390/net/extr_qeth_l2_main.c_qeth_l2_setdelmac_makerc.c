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
 int EIO ; 
 int ENOENT ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  IPA_RC_L2_ADDR_TABLE_FULL 135 
#define  IPA_RC_L2_DUP_LAYER3_MAC 134 
#define  IPA_RC_L2_DUP_MAC 133 
#define  IPA_RC_L2_MAC_NOT_AUTH_BY_ADP 132 
#define  IPA_RC_L2_MAC_NOT_AUTH_BY_HYP 131 
#define  IPA_RC_L2_MAC_NOT_FOUND 130 
#define  IPA_RC_L2_UNSUPPORTED_CMD 129 
#define  IPA_RC_SUCCESS 128 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 

__attribute__((used)) static int qeth_l2_setdelmac_makerc(struct qeth_card *card, u16 retcode)
{
	int rc;

	if (retcode)
		QETH_CARD_TEXT_(card, 2, "err%04x", retcode);
	switch (retcode) {
	case IPA_RC_SUCCESS:
		rc = 0;
		break;
	case IPA_RC_L2_UNSUPPORTED_CMD:
		rc = -EOPNOTSUPP;
		break;
	case IPA_RC_L2_ADDR_TABLE_FULL:
		rc = -ENOSPC;
		break;
	case IPA_RC_L2_DUP_MAC:
	case IPA_RC_L2_DUP_LAYER3_MAC:
		rc = -EEXIST;
		break;
	case IPA_RC_L2_MAC_NOT_AUTH_BY_HYP:
	case IPA_RC_L2_MAC_NOT_AUTH_BY_ADP:
		rc = -EPERM;
		break;
	case IPA_RC_L2_MAC_NOT_FOUND:
		rc = -ENOENT;
		break;
	default:
		rc = -EIO;
		break;
	}
	return rc;
}