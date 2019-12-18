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
struct TYPE_4__ {int /*<<< orphan*/ * vaddr; } ;
struct falcon {TYPE_2__ firmware; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  free; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int EINVAL ; 

int falcon_init(struct falcon *falcon)
{
	/* check mandatory ops */
	if (!falcon->ops || !falcon->ops->alloc || !falcon->ops->free)
		return -EINVAL;

	falcon->firmware.vaddr = NULL;

	return 0;
}