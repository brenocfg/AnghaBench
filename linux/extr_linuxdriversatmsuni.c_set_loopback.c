#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct atm_dev {TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ type; int loop_mode; } ;
struct TYPE_3__ {int (* phy_get ) (struct atm_dev*,int) ;int /*<<< orphan*/  (* phy_put ) (struct atm_dev*,unsigned char,int) ;} ;

/* Variables and functions */
#define  ATM_LM_LOC_PHY 130 
#define  ATM_LM_NONE 129 
#define  ATM_LM_RMT_PHY 128 
 int EINVAL ; 
 TYPE_2__* PRIV (struct atm_dev*) ; 
 int SUNI_MCM ; 
 int SUNI_MCM_DLE ; 
 int SUNI_MCM_LLE ; 
 int SUNI_MCT ; 
 int SUNI_MCT_DLE ; 
 int SUNI_MCT_LLE ; 
 scalar_t__ SUNI_MRI_TYPE_PM5355 ; 
 int stub1 (struct atm_dev*,int) ; 
 int /*<<< orphan*/  stub2 (struct atm_dev*,unsigned char,int) ; 

__attribute__((used)) static int set_loopback(struct atm_dev *dev,int mode)
{
	unsigned char control;
	int reg, dle, lle;

	if (PRIV(dev)->type == SUNI_MRI_TYPE_PM5355) {
		reg = SUNI_MCM;
		dle = SUNI_MCM_DLE;
		lle = SUNI_MCM_LLE;
	} else {
		reg = SUNI_MCT;
		dle = SUNI_MCT_DLE;
		lle = SUNI_MCT_LLE;
	}

	control = dev->ops->phy_get(dev, reg) & ~(dle | lle);
	switch (mode) {
		case ATM_LM_NONE:
			break;
		case ATM_LM_LOC_PHY:
			control |= dle;
			break;
		case ATM_LM_RMT_PHY:
			control |= lle;
			break;
		default:
			return -EINVAL;
	}
	dev->ops->phy_put(dev, control, reg);
	PRIV(dev)->loop_mode = mode;
	return 0;
}