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
struct ib_rdmacg_object {int /*<<< orphan*/  cg; } ;
struct ib_device {int /*<<< orphan*/  cg_device; } ;
typedef  enum rdmacg_resource_type { ____Placeholder_rdmacg_resource_type } rdmacg_resource_type ;

/* Variables and functions */
 int /*<<< orphan*/  rdmacg_uncharge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void ib_rdmacg_uncharge(struct ib_rdmacg_object *cg_obj,
			struct ib_device *device,
			enum rdmacg_resource_type resource_index)
{
	rdmacg_uncharge(cg_obj->cg, &device->cg_device,
			resource_index);
}