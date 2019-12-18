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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_property {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int cdv_intel_crt_set_property(struct drm_connector *connector,
				  struct drm_property *property,
				  uint64_t value)
{
	return 0;
}