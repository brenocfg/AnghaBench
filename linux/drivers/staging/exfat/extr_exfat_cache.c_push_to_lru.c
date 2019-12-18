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
struct buf_cache_t {struct buf_cache_t* prev; struct buf_cache_t* next; } ;

/* Variables and functions */

__attribute__((used)) static void push_to_lru(struct buf_cache_t *bp, struct buf_cache_t *list)
{
	bp->prev = list->prev;
	bp->next = list;
	list->prev->next = bp;
	list->prev = bp;
}