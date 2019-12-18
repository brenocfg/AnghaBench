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
typedef  int /*<<< orphan*/  u32 ;
struct evergreen_wm_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evergreen_data_return_bandwidth (struct evergreen_wm_params*) ; 
 int /*<<< orphan*/  evergreen_dmif_request_bandwidth (struct evergreen_wm_params*) ; 
 int /*<<< orphan*/  evergreen_dram_bandwidth (struct evergreen_wm_params*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 evergreen_available_bandwidth(struct evergreen_wm_params *wm)
{
	/* Calculate the Available bandwidth. Display can use this temporarily but not in average. */
	u32 dram_bandwidth = evergreen_dram_bandwidth(wm);
	u32 data_return_bandwidth = evergreen_data_return_bandwidth(wm);
	u32 dmif_req_bandwidth = evergreen_dmif_request_bandwidth(wm);

	return min(dram_bandwidth, min(data_return_bandwidth, dmif_req_bandwidth));
}