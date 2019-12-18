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
typedef  int /*<<< orphan*/  u32 ;
struct xhci_port {int /*<<< orphan*/  addr; } ;
struct seq_file {struct xhci_port* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_decode_portsc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xhci_portsc_show(struct seq_file *s, void *unused)
{
	struct xhci_port	*port = s->private;
	u32			portsc;

	portsc = readl(port->addr);
	seq_printf(s, "%s\n", xhci_decode_portsc(portsc));

	return 0;
}