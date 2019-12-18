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
typedef  scalar_t__ uint32_t ;
struct ddc_service {struct dc_link* link; } ;
struct TYPE_2__ {scalar_t__ branch_dev_id; int /*<<< orphan*/  branch_dev_name; } ;
struct dc_link {TYPE_1__ dpcd_caps; } ;

/* Variables and functions */
 scalar_t__ DP_BRANCH_DEVICE_ID_0080E1 ; 
 int /*<<< orphan*/  DP_DVI_CONVERTER_ID_4 ; 
 scalar_t__ I2C_OVER_AUX_DEFER_WA_DELAY ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t defer_delay_converter_wa(
	struct ddc_service *ddc,
	uint32_t defer_delay)
{
	struct dc_link *link = ddc->link;

	if (link->dpcd_caps.branch_dev_id == DP_BRANCH_DEVICE_ID_0080E1 &&
		!memcmp(link->dpcd_caps.branch_dev_name,
			DP_DVI_CONVERTER_ID_4,
			sizeof(link->dpcd_caps.branch_dev_name)))
		return defer_delay > I2C_OVER_AUX_DEFER_WA_DELAY ?
			defer_delay : I2C_OVER_AUX_DEFER_WA_DELAY;

	return defer_delay;
}