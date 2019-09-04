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
struct intel_wopcm {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int GEN9_WOPCM_SIZE ; 

void intel_wopcm_init_early(struct intel_wopcm *wopcm)
{
	wopcm->size = GEN9_WOPCM_SIZE;

	DRM_DEBUG_DRIVER("WOPCM size: %uKiB\n", wopcm->size / 1024);
}