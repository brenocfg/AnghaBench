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
struct bitmap_iterator {int advance_array; int count; unsigned long* stats_bitmap; scalar_t__ iterator; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_empty (unsigned long*,int) ; 
 int bitmap_weight (unsigned long*,int) ; 

__attribute__((used)) static inline void bitmap_iterator_init(struct bitmap_iterator *h,
					unsigned long *stats_bitmap,
					int count)
{
	h->iterator = 0;
	h->advance_array = !bitmap_empty(stats_bitmap, count);
	h->count = h->advance_array ? bitmap_weight(stats_bitmap, count)
		: count;
	h->stats_bitmap = stats_bitmap;
}