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
struct mic_smpt_hw_info {int num_reg; int page_shift; unsigned long long page_size; int base; } ;
struct mic_device {TYPE_1__* smpt; } ;
struct TYPE_2__ {struct mic_smpt_hw_info info; } ;

/* Variables and functions */

__attribute__((used)) static void mic_x100_smpt_hw_init(struct mic_device *mdev)
{
	struct mic_smpt_hw_info *info = &mdev->smpt->info;

	info->num_reg = 32;
	info->page_shift = 34;
	info->page_size = (1ULL << info->page_shift);
	info->base = 0x8000000000ULL;
}