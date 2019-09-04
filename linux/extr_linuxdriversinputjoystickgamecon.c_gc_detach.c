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
struct parport {scalar_t__ number; } ;
struct gc {scalar_t__ parportno; int /*<<< orphan*/  pd; TYPE_1__* pads; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 int GC_MAX_DEVICES ; 
 int GC_MAX_PORTS ; 
 struct gc** gc_base ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct gc*) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_detach(struct parport *port)
{
	int i;
	struct gc *gc;

	for (i = 0; i < GC_MAX_PORTS; i++) {
		if (gc_base[i] && gc_base[i]->parportno == port->number)
			break;
	}

	if (i == GC_MAX_PORTS)
		return;

	gc = gc_base[i];
	gc_base[i] = NULL;

	for (i = 0; i < GC_MAX_DEVICES; i++)
		if (gc->pads[i].dev)
			input_unregister_device(gc->pads[i].dev);
	parport_unregister_device(gc->pd);
	kfree(gc);
}