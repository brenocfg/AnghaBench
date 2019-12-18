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
struct TYPE_2__ {int /*<<< orphan*/  keybd_dev; int /*<<< orphan*/  mouse_dev; } ;
struct service_processor {TYPE_1__ remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_mouse_interrupts (struct service_processor*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 

void ibmasm_free_remote_input_dev(struct service_processor *sp)
{
	disable_mouse_interrupts(sp);
	input_unregister_device(sp->remote.mouse_dev);
	input_unregister_device(sp->remote.keybd_dev);
}