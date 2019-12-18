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
struct TYPE_2__ {scalar_t__ state; } ;
struct dm_crtc_state {TYPE_1__ freesync_config; } ;

/* Variables and functions */
 scalar_t__ VRR_STATE_ACTIVE_FIXED ; 
 scalar_t__ VRR_STATE_ACTIVE_VARIABLE ; 

__attribute__((used)) static inline bool amdgpu_dm_vrr_active(struct dm_crtc_state *dm_state)
{
	return dm_state->freesync_config.state == VRR_STATE_ACTIVE_VARIABLE ||
	       dm_state->freesync_config.state == VRR_STATE_ACTIVE_FIXED;
}