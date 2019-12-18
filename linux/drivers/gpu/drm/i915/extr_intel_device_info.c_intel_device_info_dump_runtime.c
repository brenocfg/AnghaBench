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
struct intel_runtime_info {int /*<<< orphan*/  cs_timestamp_frequency_khz; int /*<<< orphan*/  sseu; } ;
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sseu_dump (int /*<<< orphan*/ *,struct drm_printer*) ; 

void intel_device_info_dump_runtime(const struct intel_runtime_info *info,
				    struct drm_printer *p)
{
	sseu_dump(&info->sseu, p);

	drm_printf(p, "CS timestamp frequency: %u kHz\n",
		   info->cs_timestamp_frequency_khz);
}