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
typedef  int uint8_t ;
struct dc {int dummy; } ;
struct amdgpu_dm_connector {scalar_t__ dc_link; } ;
typedef  int /*<<< orphan*/  dpcd_data ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DOWN_STREAM_PORT_COUNT ; 
 int DP_MSA_TIMING_PAR_IGNORED ; 
 scalar_t__ dm_helpers_dp_read_dpcd (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static bool is_dp_capable_without_timing_msa(struct dc *dc,
					     struct amdgpu_dm_connector *amdgpu_dm_connector)
{
	uint8_t dpcd_data;
	bool capable = false;

	if (amdgpu_dm_connector->dc_link &&
		dm_helpers_dp_read_dpcd(
				NULL,
				amdgpu_dm_connector->dc_link,
				DP_DOWN_STREAM_PORT_COUNT,
				&dpcd_data,
				sizeof(dpcd_data))) {
		capable = (dpcd_data & DP_MSA_TIMING_PAR_IGNORED) ? true:false;
	}

	return capable;
}