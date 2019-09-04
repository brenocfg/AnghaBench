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
struct xfrm_state {TYPE_1__* aead; } ;
struct ipsec_sa_entry {int authsize; } ;
struct TYPE_2__ {int alg_icv_len; } ;

/* Variables and functions */
 int CHCR_SCMD_HMAC_CTRL_DIV2 ; 
 int CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT ; 
 int CHCR_SCMD_HMAC_CTRL_NO_TRUNC ; 
 int EINVAL ; 
#define  ICV_12 130 
#define  ICV_16 129 
#define  ICV_8 128 

__attribute__((used)) static inline int chcr_ipsec_setauthsize(struct xfrm_state *x,
					 struct ipsec_sa_entry *sa_entry)
{
	int hmac_ctrl;
	int authsize = x->aead->alg_icv_len / 8;

	sa_entry->authsize = authsize;

	switch (authsize) {
	case ICV_8:
		hmac_ctrl = CHCR_SCMD_HMAC_CTRL_DIV2;
		break;
	case ICV_12:
		hmac_ctrl = CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT;
		break;
	case ICV_16:
		hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		break;
	default:
		return -EINVAL;
	}
	return hmac_ctrl;
}