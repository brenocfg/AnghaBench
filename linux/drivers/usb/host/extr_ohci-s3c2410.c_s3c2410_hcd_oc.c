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
struct s3c2410_hcd_port {int flags; int oc_status; int oc_changed; } ;
struct s3c2410_hcd_info {struct s3c2410_hcd_port* port; } ;

/* Variables and functions */
 int S3C_HCDFLG_USED ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  s3c2410_usb_set_power (struct s3c2410_hcd_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2410_hcd_oc(struct s3c2410_hcd_info *info, int port_oc)
{
	struct s3c2410_hcd_port *port;
	unsigned long flags;
	int portno;

	if (info == NULL)
		return;

	port = &info->port[0];

	local_irq_save(flags);

	for (portno = 0; portno < 2; port++, portno++) {
		if (port_oc & (1<<portno) &&
		    port->flags & S3C_HCDFLG_USED) {
			port->oc_status = 1;
			port->oc_changed = 1;

			/* ok, once over-current is detected,
			   the port needs to be powered down */
			s3c2410_usb_set_power(info, portno+1, 0);
		}
	}

	local_irq_restore(flags);
}