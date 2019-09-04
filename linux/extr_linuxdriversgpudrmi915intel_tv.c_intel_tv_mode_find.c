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
struct tv_mode {int dummy; } ;
struct TYPE_2__ {int mode; } ;
struct drm_connector_state {TYPE_1__ tv; } ;

/* Variables and functions */
 struct tv_mode const* tv_modes ; 

__attribute__((used)) static const struct tv_mode *intel_tv_mode_find(const struct drm_connector_state *conn_state)
{
	int format = conn_state->tv.mode;

	return &tv_modes[format];
}