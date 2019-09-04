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
struct hci_uart {unsigned int init_speed; unsigned int oper_speed; } ;

/* Variables and functions */

void hci_uart_set_speeds(struct hci_uart *hu, unsigned int init_speed,
			 unsigned int oper_speed)
{
	hu->init_speed = init_speed;
	hu->oper_speed = oper_speed;
}