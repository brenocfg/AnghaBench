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
struct buf_cache_t {TYPE_2__* prev; TYPE_1__* next; } ;
struct TYPE_4__ {TYPE_1__* next; } ;
struct TYPE_3__ {TYPE_2__* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  push_to_mru (struct buf_cache_t*,struct buf_cache_t*) ; 

__attribute__((used)) static void move_to_mru(struct buf_cache_t *bp, struct buf_cache_t *list)
{
	bp->prev->next = bp->next;
	bp->next->prev = bp->prev;
	push_to_mru(bp, list);
}