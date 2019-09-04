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
 int /*<<< orphan*/  DPU_DEBUG (char*,void*) ; 
 int /*<<< orphan*/  dpu_hw_blk_put (void*) ; 

__attribute__((used)) static void _dpu_crtc_hw_blk_put(void *val)
{
	DPU_DEBUG("res://%pK\n", val);
	dpu_hw_blk_put(val);
}