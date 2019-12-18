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
 int EACCES ; 
 int EALREADY ; 
 int EBUSY ; 
 int EIO ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
#define  IPA_RC_L2_ADDR_TABLE_FULL 134 
#define  IPA_RC_L2_MAC_NOT_AUTH_BY_ADP 133 
#define  IPA_RC_L2_UNSUPPORTED_CMD 132 
#define  IPA_RC_NOTSUPP 131 
#define  IPA_RC_SUCCESS 130 
#define  IPA_RC_VNICC_OOSEQ 129 
#define  IPA_RC_VNICC_VNICBP 128 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 

__attribute__((used)) static int qeth_l2_vnicc_makerc(struct qeth_card *card, u16 ipa_rc)
{
	int rc;

	switch (ipa_rc) {
	case IPA_RC_SUCCESS:
		return ipa_rc;
	case IPA_RC_L2_UNSUPPORTED_CMD:
	case IPA_RC_NOTSUPP:
		rc = -EOPNOTSUPP;
		break;
	case IPA_RC_VNICC_OOSEQ:
		rc = -EALREADY;
		break;
	case IPA_RC_VNICC_VNICBP:
		rc = -EBUSY;
		break;
	case IPA_RC_L2_ADDR_TABLE_FULL:
		rc = -ENOSPC;
		break;
	case IPA_RC_L2_MAC_NOT_AUTH_BY_ADP:
		rc = -EACCES;
		break;
	default:
		rc = -EIO;
	}

	QETH_CARD_TEXT_(card, 2, "err%04x", ipa_rc);
	return rc;
}