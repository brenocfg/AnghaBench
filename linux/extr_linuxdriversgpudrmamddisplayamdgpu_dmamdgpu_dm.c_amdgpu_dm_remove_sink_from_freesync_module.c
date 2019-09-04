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
struct drm_connector {int dummy; } ;

/* Variables and functions */

void amdgpu_dm_remove_sink_from_freesync_module(struct drm_connector *connector)
{
	/*
	 * TODO fill in once we figure out how to deal with freesync in
	 * an upstreamable fashion
	 */
}