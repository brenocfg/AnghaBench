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
struct dce10_wm_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce_v11_0_data_return_bandwidth (struct dce10_wm_params*) ; 
 int /*<<< orphan*/  dce_v11_0_dmif_request_bandwidth (struct dce10_wm_params*) ; 
 int /*<<< orphan*/  dce_v11_0_dram_bandwidth (struct dce10_wm_params*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 dce_v11_0_available_bandwidth(struct dce10_wm_params *wm)
{
	/* Calculate the Available bandwidth. Display can use this temporarily but not in average. */
	u32 dram_bandwidth = dce_v11_0_dram_bandwidth(wm);
	u32 data_return_bandwidth = dce_v11_0_data_return_bandwidth(wm);
	u32 dmif_req_bandwidth = dce_v11_0_dmif_request_bandwidth(wm);

	return min(dram_bandwidth, min(data_return_bandwidth, dmif_req_bandwidth));
}