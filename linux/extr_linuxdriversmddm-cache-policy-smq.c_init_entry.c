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
struct entry {unsigned int level; int dirty; int allocated; int sentinel; int pending_work; void* prev; void* next; void* hash_next; } ;

/* Variables and functions */
 void* INDEXER_NULL ; 

__attribute__((used)) static void init_entry(struct entry *e)
{
	/*
	 * We can't memset because that would clear the hotspot and
	 * sentinel bits which remain constant.
	 */
	e->hash_next = INDEXER_NULL;
	e->next = INDEXER_NULL;
	e->prev = INDEXER_NULL;
	e->level = 0u;
	e->dirty = true;	/* FIXME: audit */
	e->allocated = true;
	e->sentinel = false;
	e->pending_work = false;
}