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
struct uart_port {int /*<<< orphan*/  mapbase; scalar_t__ membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZS_CHAN_IO_SIZE ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zs_release_port(struct uart_port *uport)
{
	iounmap(uport->membase);
	uport->membase = 0;
	release_mem_region(uport->mapbase, ZS_CHAN_IO_SIZE);
}