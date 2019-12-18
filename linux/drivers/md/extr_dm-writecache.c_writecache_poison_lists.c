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
struct TYPE_4__ {void* prev; void* next; } ;
struct TYPE_3__ {void* prev; void* next; } ;
struct dm_writecache {TYPE_2__ freelist; TYPE_1__ lru; int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 void* LIST_POISON1 ; 
 void* LIST_POISON2 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void writecache_poison_lists(struct dm_writecache *wc)
{
	/*
	 * Catch incorrect access to these values while the device is suspended.
	 */
	memset(&wc->tree, -1, sizeof wc->tree);
	wc->lru.next = LIST_POISON1;
	wc->lru.prev = LIST_POISON2;
	wc->freelist.next = LIST_POISON1;
	wc->freelist.prev = LIST_POISON2;
}