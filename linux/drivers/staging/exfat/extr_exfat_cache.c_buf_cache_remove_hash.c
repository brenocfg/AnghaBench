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
struct buf_cache_t {TYPE_2__* hash_prev; TYPE_1__* hash_next; } ;
struct TYPE_4__ {TYPE_1__* hash_next; } ;
struct TYPE_3__ {TYPE_2__* hash_prev; } ;

/* Variables and functions */

__attribute__((used)) static void buf_cache_remove_hash(struct buf_cache_t *bp)
{
	(bp->hash_prev)->hash_next = bp->hash_next;
	(bp->hash_next)->hash_prev = bp->hash_prev;
}