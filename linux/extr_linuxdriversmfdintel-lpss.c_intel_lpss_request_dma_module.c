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

/* Variables and functions */
 int request_module (char*,char const*) ; 

__attribute__((used)) static int intel_lpss_request_dma_module(const char *name)
{
	static bool intel_lpss_dma_requested;

	if (intel_lpss_dma_requested)
		return 0;

	intel_lpss_dma_requested = true;
	return request_module("%s", name);
}