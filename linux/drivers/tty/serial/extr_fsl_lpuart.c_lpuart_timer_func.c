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
struct timer_list {int dummy; } ;
struct lpuart_port {int dummy; } ;

/* Variables and functions */
 struct lpuart_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart_copy_rx_to_tty (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_timer ; 
 struct lpuart_port* sport ; 

__attribute__((used)) static void lpuart_timer_func(struct timer_list *t)
{
	struct lpuart_port *sport = from_timer(sport, t, lpuart_timer);

	lpuart_copy_rx_to_tty(sport);
}