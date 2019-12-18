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
typedef  void* u16 ;
struct TYPE_4__ {unsigned long x; unsigned long y; } ;
struct TYPE_3__ {void* y; void* x; } ;
struct tcm_area {TYPE_2__ p0; TYPE_1__ p1; } ;
struct tcm {unsigned long width; int /*<<< orphan*/  lock; int /*<<< orphan*/  map_size; int /*<<< orphan*/  bitmap; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int l2r_t2b (void*,void*,void*,int /*<<< orphan*/ ,unsigned long*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 sita_reserve_2d(struct tcm *tcm, u16 h, u16 w, u16 align,
				s16 offset, u16 slot_bytes,
				struct tcm_area *area)
{
	unsigned long pos;
	int ret;

	spin_lock(&(tcm->lock));
	ret = l2r_t2b(w, h, align, offset, &pos, slot_bytes, tcm->bitmap,
			tcm->map_size, tcm->width);

	if (!ret) {
		area->p0.x = pos % tcm->width;
		area->p0.y = pos / tcm->width;
		area->p1.x = area->p0.x + w - 1;
		area->p1.y = area->p0.y + h - 1;
	}
	spin_unlock(&(tcm->lock));

	return ret;
}