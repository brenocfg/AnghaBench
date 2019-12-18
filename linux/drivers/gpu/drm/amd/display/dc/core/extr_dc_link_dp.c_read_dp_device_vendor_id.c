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
typedef  int /*<<< orphan*/  uint8_t ;
struct dp_device_vendor_id {int* ieee_oui; int /*<<< orphan*/  ieee_device_id; } ;
struct TYPE_2__ {int branch_dev_id; int /*<<< orphan*/  branch_dev_name; } ;
struct dc_link {TYPE_1__ dpcd_caps; } ;
typedef  int /*<<< orphan*/  dp_id ;

/* Variables and functions */
 int /*<<< orphan*/  DP_BRANCH_OUI ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void read_dp_device_vendor_id(struct dc_link *link)
{
	struct dp_device_vendor_id dp_id;

	/* read IEEE branch device id */
	core_link_read_dpcd(
		link,
		DP_BRANCH_OUI,
		(uint8_t *)&dp_id,
		sizeof(dp_id));

	link->dpcd_caps.branch_dev_id =
		(dp_id.ieee_oui[0] << 16) +
		(dp_id.ieee_oui[1] << 8) +
		dp_id.ieee_oui[2];

	memmove(
		link->dpcd_caps.branch_dev_name,
		dp_id.ieee_device_id,
		sizeof(dp_id.ieee_device_id));
}