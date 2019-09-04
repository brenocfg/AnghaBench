#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int on_st; } ;
struct bfq_queue {int ref; int allocated; TYPE_1__ entity; } ;

/* Variables and functions */

__attribute__((used)) static int bfqq_process_refs(struct bfq_queue *bfqq)
{
	return bfqq->ref - bfqq->allocated - bfqq->entity.on_st;
}