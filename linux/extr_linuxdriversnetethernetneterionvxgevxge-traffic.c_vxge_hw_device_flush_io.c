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
typedef  int /*<<< orphan*/  u32 ;
struct __vxge_hw_device {TYPE_1__* common_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  titan_general_int_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 

void vxge_hw_device_flush_io(struct __vxge_hw_device *hldev)
{
	u32 val32;

	val32 = readl(&hldev->common_reg->titan_general_int_status);
}