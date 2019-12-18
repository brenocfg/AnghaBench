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
struct buf_cache_t {struct buf_cache_t* next; struct buf_cache_t* prev; } ;

/* Variables and functions */

__attribute__((used)) static void push_to_mru(struct buf_cache_t *bp, struct buf_cache_t *list)
{
	bp->next = list->next;
	bp->prev = list;
	list->next->prev = bp;
	list->next = bp;
}