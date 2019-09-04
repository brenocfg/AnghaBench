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
struct rb_node {int dummy; } ;
struct TYPE_4__ {TYPE_1__* tsk; } ;
struct TYPE_3__ {int prio; } ;

/* Variables and functions */
 TYPE_2__* to_wait (struct rb_node*) ; 

__attribute__((used)) static inline bool chain_wakeup(struct rb_node *rb, int priority)
{
	return rb && to_wait(rb)->tsk->prio <= priority;
}