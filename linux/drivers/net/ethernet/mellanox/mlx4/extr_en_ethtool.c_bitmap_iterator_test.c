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
struct bitmap_iterator {int /*<<< orphan*/  stats_bitmap; int /*<<< orphan*/  iterator; int /*<<< orphan*/  advance_array; } ;

/* Variables and functions */
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bitmap_iterator_test(struct bitmap_iterator *h)
{
	return !h->advance_array ? 1 : test_bit(h->iterator, h->stats_bitmap);
}