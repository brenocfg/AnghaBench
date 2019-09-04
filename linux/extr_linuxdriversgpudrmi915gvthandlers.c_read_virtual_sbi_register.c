#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int number; TYPE_2__* registers; } ;
struct intel_vgpu_display {TYPE_1__ sbi; } ;
struct intel_vgpu {struct intel_vgpu_display display; } ;
struct TYPE_4__ {unsigned int offset; int /*<<< orphan*/  value; } ;

/* Variables and functions */

__attribute__((used)) static u32 read_virtual_sbi_register(struct intel_vgpu *vgpu,
		unsigned int sbi_offset)
{
	struct intel_vgpu_display *display = &vgpu->display;
	int num = display->sbi.number;
	int i;

	for (i = 0; i < num; ++i)
		if (display->sbi.registers[i].offset == sbi_offset)
			break;

	if (i == num)
		return 0;

	return display->sbi.registers[i].value;
}