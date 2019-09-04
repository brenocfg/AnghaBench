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
struct binder_alloc {int dummy; } ;

/* Variables and functions */
 int BUFFER_NUM ; 
 int /*<<< orphan*/  binder_selftest_alloc_free (struct binder_alloc*,size_t*,int*,size_t) ; 
 scalar_t__ is_dup (int*,int,int) ; 

__attribute__((used)) static void binder_selftest_free_seq(struct binder_alloc *alloc,
				     size_t *sizes, int *seq,
				     int index, size_t end)
{
	int i;

	if (index == BUFFER_NUM) {
		binder_selftest_alloc_free(alloc, sizes, seq, end);
		return;
	}
	for (i = 0; i < BUFFER_NUM; i++) {
		if (is_dup(seq, index, i))
			continue;
		seq[index] = i;
		binder_selftest_free_seq(alloc, sizes, seq, index + 1, end);
	}
}