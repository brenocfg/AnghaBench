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
struct btree {int /*<<< orphan*/  seq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void rw_lock(bool w, struct btree *b, int level)
{
	w ? down_write_nested(&b->lock, level + 1)
	  : down_read_nested(&b->lock, level + 1);
	if (w)
		b->seq++;
}