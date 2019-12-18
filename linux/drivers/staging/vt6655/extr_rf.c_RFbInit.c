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
struct vnt_private {int byRFType; int /*<<< orphan*/  byMaxPwrLevel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL2230_PWR_IDX_LEN ; 
 int /*<<< orphan*/  AL7230_PWR_IDX_LEN ; 
#define  RF_AIROHA 131 
#define  RF_AIROHA7230 130 
#define  RF_AL2230S 129 
#define  RF_NOTHING 128 
 int RFbAL2230Init (struct vnt_private*) ; 
 int s_bAL7230Init (struct vnt_private*) ; 

bool RFbInit(struct vnt_private *priv)
{
	bool ret = true;

	switch (priv->byRFType) {
	case RF_AIROHA:
	case RF_AL2230S:
		priv->byMaxPwrLevel = AL2230_PWR_IDX_LEN;
		ret = RFbAL2230Init(priv);
		break;
	case RF_AIROHA7230:
		priv->byMaxPwrLevel = AL7230_PWR_IDX_LEN;
		ret = s_bAL7230Init(priv);
		break;
	case RF_NOTHING:
		ret = true;
		break;
	default:
		ret = false;
		break;
	}
	return ret;
}