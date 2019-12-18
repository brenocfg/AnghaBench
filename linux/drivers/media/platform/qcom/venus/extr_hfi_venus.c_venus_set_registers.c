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
struct venus_resources {unsigned int reg_tbl_size; struct reg_val* reg_tbl; } ;
struct venus_hfi_device {TYPE_1__* core; } ;
struct reg_val {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {struct venus_resources* res; } ;

/* Variables and functions */
 int /*<<< orphan*/  venus_writel (struct venus_hfi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void venus_set_registers(struct venus_hfi_device *hdev)
{
	const struct venus_resources *res = hdev->core->res;
	const struct reg_val *tbl = res->reg_tbl;
	unsigned int count = res->reg_tbl_size;
	unsigned int i;

	for (i = 0; i < count; i++)
		venus_writel(hdev, tbl[i].reg, tbl[i].value);
}