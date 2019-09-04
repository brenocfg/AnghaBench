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
struct ib_rdmacg_object {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum rdmacg_resource_type { ____Placeholder_rdmacg_resource_type } rdmacg_resource_type ;

/* Variables and functions */

__attribute__((used)) static inline void ib_rdmacg_uncharge(struct ib_rdmacg_object *cg_obj,
				      struct ib_device *device,
				      enum rdmacg_resource_type resource_index)
{ }