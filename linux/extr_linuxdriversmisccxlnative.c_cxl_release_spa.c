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
struct cxl_afu {TYPE_1__* native; } ;
struct TYPE_2__ {int /*<<< orphan*/ * spa; int /*<<< orphan*/  spa_order; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 

void cxl_release_spa(struct cxl_afu *afu)
{
	if (afu->native->spa) {
		free_pages((unsigned long) afu->native->spa,
			afu->native->spa_order);
		afu->native->spa = NULL;
	}
}