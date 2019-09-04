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
typedef  int /*<<< orphan*/  u32 ;
struct sysc {int module_size; int /*<<< orphan*/  module_va; int /*<<< orphan*/  module_pa; int /*<<< orphan*/  dev; int /*<<< orphan*/ * offsets; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 size_t SYSC_REVISION ; 
 size_t SYSC_SYSCONFIG ; 
 size_t SYSC_SYSSTATUS ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysc_ioremap(struct sysc *ddata)
{
	int size;

	size = max3(ddata->offsets[SYSC_REVISION],
		    ddata->offsets[SYSC_SYSCONFIG],
		    ddata->offsets[SYSC_SYSSTATUS]);

	if (size < 0 || (size + sizeof(u32)) > ddata->module_size)
		return -EINVAL;

	ddata->module_va = devm_ioremap(ddata->dev,
					ddata->module_pa,
					size + sizeof(u32));
	if (!ddata->module_va)
		return -EIO;

	return 0;
}