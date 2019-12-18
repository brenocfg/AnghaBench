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
struct uart_port {int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; } ;
struct dz_mux {int /*<<< orphan*/  map_guard; } ;
struct TYPE_2__ {struct dz_mux* mux; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dec_kn_slot_size ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_dport (struct uart_port*) ; 

__attribute__((used)) static void dz_release_port(struct uart_port *uport)
{
	struct dz_mux *mux = to_dport(uport)->mux;
	int map_guard;

	iounmap(uport->membase);
	uport->membase = NULL;

	map_guard = atomic_add_return(-1, &mux->map_guard);
	if (!map_guard)
		release_mem_region(uport->mapbase, dec_kn_slot_size);
}