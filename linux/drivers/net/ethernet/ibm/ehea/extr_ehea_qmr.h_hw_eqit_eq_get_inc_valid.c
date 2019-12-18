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
typedef  int u8 ;
typedef  int u32 ;
struct hw_queue {int toggle_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_qeit_eq_get_inc (struct hw_queue*) ; 
 void* hw_qeit_get (struct hw_queue*) ; 

__attribute__((used)) static inline void *hw_eqit_eq_get_inc_valid(struct hw_queue *queue)
{
	void *retvalue = hw_qeit_get(queue);
	u32 qe = *(u8 *)retvalue;
	if ((qe >> 7) == (queue->toggle_state & 1))
		hw_qeit_eq_get_inc(queue);
	else
		retvalue = NULL;
	return retvalue;
}