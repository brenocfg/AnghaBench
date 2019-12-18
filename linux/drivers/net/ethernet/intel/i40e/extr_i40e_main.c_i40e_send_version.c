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
struct i40e_pf {int /*<<< orphan*/  hw; } ;
struct i40e_driver_version {int /*<<< orphan*/  driver_string; scalar_t__ subbuild_version; int /*<<< orphan*/  build_version; int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_VERSION ; 
 int /*<<< orphan*/  DRV_VERSION_BUILD ; 
 int /*<<< orphan*/  DRV_VERSION_MAJOR ; 
 int /*<<< orphan*/  DRV_VERSION_MINOR ; 
 int /*<<< orphan*/  i40e_aq_send_driver_version (int /*<<< orphan*/ *,struct i40e_driver_version*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40e_send_version(struct i40e_pf *pf)
{
	struct i40e_driver_version dv;

	dv.major_version = DRV_VERSION_MAJOR;
	dv.minor_version = DRV_VERSION_MINOR;
	dv.build_version = DRV_VERSION_BUILD;
	dv.subbuild_version = 0;
	strlcpy(dv.driver_string, DRV_VERSION, sizeof(dv.driver_string));
	i40e_aq_send_driver_version(&pf->hw, &dv, NULL);
}