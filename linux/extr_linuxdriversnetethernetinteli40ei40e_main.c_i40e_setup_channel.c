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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_vsi {scalar_t__ type; } ;
struct i40e_pf {size_t lan_vsi; TYPE_2__* pdev; TYPE_1__** vsi; } ;
struct i40e_channel {scalar_t__ initialized; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  uplink_seid; } ;

/* Variables and functions */
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  I40E_VSI_VMDQ2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int i40e_setup_hw_channel (struct i40e_pf*,struct i40e_vsi*,struct i40e_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i40e_setup_channel(struct i40e_pf *pf, struct i40e_vsi *vsi,
			       struct i40e_channel *ch)
{
	u8 vsi_type;
	u16 seid;
	int ret;

	if (vsi->type == I40E_VSI_MAIN) {
		vsi_type = I40E_VSI_VMDQ2;
	} else {
		dev_err(&pf->pdev->dev, "unsupported parent vsi type(%d)\n",
			vsi->type);
		return false;
	}

	/* underlying switching element */
	seid = pf->vsi[pf->lan_vsi]->uplink_seid;

	/* create channel (VSI), configure TX rings */
	ret = i40e_setup_hw_channel(pf, vsi, ch, seid, vsi_type);
	if (ret) {
		dev_err(&pf->pdev->dev, "failed to setup hw_channel\n");
		return false;
	}

	return ch->initialized ? true : false;
}