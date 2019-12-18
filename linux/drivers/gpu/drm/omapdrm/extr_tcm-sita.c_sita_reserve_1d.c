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
typedef  unsigned long u32 ;
struct TYPE_4__ {unsigned long x; unsigned long y; } ;
struct TYPE_3__ {unsigned long x; unsigned long y; } ;
struct tcm_area {TYPE_2__ p1; TYPE_1__ p0; } ;
struct tcm {unsigned long width; int /*<<< orphan*/  lock; int /*<<< orphan*/  map_size; int /*<<< orphan*/  bitmap; } ;
typedef  int s32 ;

/* Variables and functions */
 int r2l_b2t_1d (unsigned long,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 sita_reserve_1d(struct tcm *tcm, u32 num_slots,
			   struct tcm_area *area)
{
	unsigned long pos;
	int ret;

	spin_lock(&(tcm->lock));
	ret = r2l_b2t_1d(num_slots, &pos, tcm->bitmap, tcm->map_size);
	if (!ret) {
		area->p0.x = pos % tcm->width;
		area->p0.y = pos / tcm->width;
		area->p1.x = (pos + num_slots - 1) % tcm->width;
		area->p1.y = (pos + num_slots - 1) / tcm->width;
	}
	spin_unlock(&(tcm->lock));

	return ret;
}