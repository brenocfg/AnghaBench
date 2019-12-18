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
struct muram_info {scalar_t__ vbase; } ;

/* Variables and functions */

unsigned long fman_muram_offset_to_vbase(struct muram_info *muram,
					 unsigned long offset)
{
	return offset + (unsigned long)muram->vbase;
}