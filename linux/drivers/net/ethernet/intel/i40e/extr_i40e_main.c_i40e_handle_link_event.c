#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i40e_pf {int flags; TYPE_3__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
struct i40e_arq_event_info {TYPE_2__ desc; } ;
struct i40e_aqc_get_link_status {scalar_t__ phy_type; int link_info; int an_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I40E_AQ_LINK_UP ; 
 int I40E_AQ_MEDIA_AVAILABLE ; 
 int I40E_AQ_QUALIFIED_MODULE ; 
 int I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED ; 
 scalar_t__ I40E_PHY_TYPE_NOT_SUPPORTED_HIGH_TEMP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_link_event (struct i40e_pf*) ; 

__attribute__((used)) static void i40e_handle_link_event(struct i40e_pf *pf,
				   struct i40e_arq_event_info *e)
{
	struct i40e_aqc_get_link_status *status =
		(struct i40e_aqc_get_link_status *)&e->desc.params.raw;

	/* Do a new status request to re-enable LSE reporting
	 * and load new status information into the hw struct
	 * This completely ignores any state information
	 * in the ARQ event info, instead choosing to always
	 * issue the AQ update link status command.
	 */
	i40e_link_event(pf);

	/* Check if module meets thermal requirements */
	if (status->phy_type == I40E_PHY_TYPE_NOT_SUPPORTED_HIGH_TEMP) {
		dev_err(&pf->pdev->dev,
			"Rx/Tx is disabled on this device because the module does not meet thermal requirements.\n");
		dev_err(&pf->pdev->dev,
			"Refer to the Intel(R) Ethernet Adapters and Devices User Guide for a list of supported modules.\n");
	} else {
		/* check for unqualified module, if link is down, suppress
		 * the message if link was forced to be down.
		 */
		if ((status->link_info & I40E_AQ_MEDIA_AVAILABLE) &&
		    (!(status->an_info & I40E_AQ_QUALIFIED_MODULE)) &&
		    (!(status->link_info & I40E_AQ_LINK_UP)) &&
		    (!(pf->flags & I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED))) {
			dev_err(&pf->pdev->dev,
				"Rx/Tx is disabled on this device because an unsupported SFP module type was detected.\n");
			dev_err(&pf->pdev->dev,
				"Refer to the Intel(R) Ethernet Adapters and Devices User Guide for a list of supported modules.\n");
		}
	}
}