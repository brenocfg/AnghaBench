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

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int IRQ_READ ; 
 int IRQ_WRITE ; 

int os_event_mask(int irq_type)
{
	if (irq_type == IRQ_READ)
		return EPOLLIN | EPOLLPRI;
	if (irq_type == IRQ_WRITE)
		return EPOLLOUT;
	return 0;
}