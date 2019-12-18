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
typedef  int uint64_t ;
typedef  int u32 ;
struct softing {int /*<<< orphan*/  ts_overflow; int /*<<< orphan*/  ts_ref; TYPE_1__* pdat; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {scalar_t__ freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

ktime_t softing_raw2ktime(struct softing *card, u32 raw)
{
	uint64_t rawl;
	ktime_t now, real_offset;
	ktime_t target;
	ktime_t tmp;

	now = ktime_get();
	real_offset = ktime_sub(ktime_get_real(), now);

	/* find nsec from card */
	rawl = raw * 16;
	do_div(rawl, card->pdat->freq ?: 16);
	target = ktime_add_us(card->ts_ref, rawl);
	/* test for overflows */
	tmp = ktime_add(target, card->ts_overflow);
	while (unlikely(ktime_to_ns(tmp) > ktime_to_ns(now))) {
		card->ts_ref = ktime_add(card->ts_ref, card->ts_overflow);
		target = tmp;
		tmp = ktime_add(target, card->ts_overflow);
	}
	return ktime_add(target, real_offset);
}