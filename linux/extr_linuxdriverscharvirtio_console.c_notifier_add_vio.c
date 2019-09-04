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
struct port {int dummy; } ;
struct hvc_struct {int irq_requested; int /*<<< orphan*/  vtermno; } ;

/* Variables and functions */
 int EINVAL ; 
 struct port* find_port_by_vtermno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resize_console (struct port*) ; 

__attribute__((used)) static int notifier_add_vio(struct hvc_struct *hp, int data)
{
	struct port *port;

	port = find_port_by_vtermno(hp->vtermno);
	if (!port)
		return -EINVAL;

	hp->irq_requested = 1;
	resize_console(port);

	return 0;
}