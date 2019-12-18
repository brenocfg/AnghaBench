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
struct uart_port {int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; } ;
struct sbd_port {int /*<<< orphan*/ * memctrl; struct sbd_duart* duart; } ;
struct sbd_duart {int /*<<< orphan*/  mapctrl; int /*<<< orphan*/  map_guard; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUART_CHANREG_SPACING ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sbd_port* to_sport (struct uart_port*) ; 

__attribute__((used)) static void sbd_release_port(struct uart_port *uport)
{
	struct sbd_port *sport = to_sport(uport);
	struct sbd_duart *duart = sport->duart;

	iounmap(sport->memctrl);
	sport->memctrl = NULL;
	iounmap(uport->membase);
	uport->membase = NULL;

	if(refcount_dec_and_test(&duart->map_guard))
		release_mem_region(duart->mapctrl, DUART_CHANREG_SPACING);
	release_mem_region(uport->mapbase, DUART_CHANREG_SPACING);
}