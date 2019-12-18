#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct lpuart_port {TYPE_1__ lpuart_timer; scalar_t__ dma_rx_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lpuart_timer_func ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_dma_timer_init(struct lpuart_port *sport)
{
	timer_setup(&sport->lpuart_timer, lpuart_timer_func, 0);
	sport->lpuart_timer.expires = jiffies + sport->dma_rx_timeout;
	add_timer(&sport->lpuart_timer);
}