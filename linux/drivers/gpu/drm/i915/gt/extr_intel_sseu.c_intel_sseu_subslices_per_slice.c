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
typedef  size_t u8 ;
struct sseu_dev_info {int /*<<< orphan*/ * subslice_mask; } ;

/* Variables and functions */
 unsigned int hweight8 (int /*<<< orphan*/ ) ; 

unsigned int
intel_sseu_subslices_per_slice(const struct sseu_dev_info *sseu, u8 slice)
{
	return hweight8(sseu->subslice_mask[slice]);
}