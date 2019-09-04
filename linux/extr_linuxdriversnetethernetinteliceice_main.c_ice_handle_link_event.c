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
struct ice_port_info {int dummy; } ;
struct TYPE_3__ {struct ice_port_info* port_info; } ;
struct ice_pf {TYPE_2__* pdev; TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int ice_link_event (struct ice_pf*,struct ice_port_info*) ; 

__attribute__((used)) static int ice_handle_link_event(struct ice_pf *pf)
{
	struct ice_port_info *port_info;
	int status;

	port_info = pf->hw.port_info;
	if (!port_info)
		return -EINVAL;

	status = ice_link_event(pf, port_info);
	if (status)
		dev_dbg(&pf->pdev->dev,
			"Could not process link event, error %d\n", status);

	return status;
}