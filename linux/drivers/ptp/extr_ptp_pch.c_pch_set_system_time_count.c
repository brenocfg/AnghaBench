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
struct pch_dev {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  stl_max_set_en; int /*<<< orphan*/  stl_max_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_set_system_time_count(struct pch_dev *chip)
{
	iowrite32(0x01, &chip->regs->stl_max_set_en);
	iowrite32(0xFFFFFFFF, &chip->regs->stl_max_set);
	iowrite32(0x00, &chip->regs->stl_max_set_en);
}