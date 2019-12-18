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
struct drm_dp_payload {scalar_t__ payload_state; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int drm_dp_destroy_payload_step2(struct drm_dp_mst_topology_mgr *mgr,
					int id,
					struct drm_dp_payload *payload)
{
	payload->payload_state = 0;
	return 0;
}