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
typedef  int u32 ;
struct nvkm_event {int* refs; int types_nr; TYPE_1__* func; int /*<<< orphan*/  refs_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct nvkm_event*,int,int) ;} ;

/* Variables and functions */
 int __ffs (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_event*,int,int) ; 

void
nvkm_event_get(struct nvkm_event *event, u32 types, int index)
{
	assert_spin_locked(&event->refs_lock);
	while (types) {
		int type = __ffs(types); types &= ~(1 << type);
		if (++event->refs[index * event->types_nr + type] == 1) {
			if (event->func->init)
				event->func->init(event, 1 << type, index);
		}
	}
}