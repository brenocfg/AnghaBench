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
struct softing {int /*<<< orphan*/  ts_overflow; TYPE_1__* pdat; int /*<<< orphan*/  ts_ref; } ;
struct TYPE_2__ {scalar_t__ freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void softing_initialize_timestamp(struct softing *card)
{
	uint64_t ovf;

	card->ts_ref = ktime_get();

	/* 16MHz is the reference */
	ovf = 0x100000000ULL * 16;
	do_div(ovf, card->pdat->freq ?: 16);

	card->ts_overflow = ktime_add_us(0, ovf);
}