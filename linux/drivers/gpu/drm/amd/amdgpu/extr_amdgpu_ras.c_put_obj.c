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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct ras_manager {scalar_t__ use; TYPE_1__ head; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void put_obj(struct ras_manager *obj)
{
	if (obj && --obj->use == 0)
		list_del(&obj->node);
	if (obj && obj->use < 0) {
		 DRM_ERROR("RAS ERROR: Unbalance obj(%s) use\n", obj->head.name);
	}
}