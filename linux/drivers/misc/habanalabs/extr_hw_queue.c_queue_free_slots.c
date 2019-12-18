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
typedef  int u32 ;
struct hl_hw_queue {int pi; int ci; } ;

/* Variables and functions */
 int abs (int) ; 

__attribute__((used)) static inline int queue_free_slots(struct hl_hw_queue *q, u32 queue_len)
{
	int delta = (q->pi - q->ci);

	if (delta >= 0)
		return (queue_len - delta);
	else
		return (abs(delta) - queue_len);
}