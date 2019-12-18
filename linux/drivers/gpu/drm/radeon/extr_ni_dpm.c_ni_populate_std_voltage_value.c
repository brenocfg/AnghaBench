#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ NISLANDS_SMC_VOLTAGE_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_populate_std_voltage_value(struct radeon_device *rdev,
					  u16 value, u8 index,
					  NISLANDS_SMC_VOLTAGE_VALUE *voltage)
{
	voltage->index = index;
	voltage->value = cpu_to_be16(value);
}