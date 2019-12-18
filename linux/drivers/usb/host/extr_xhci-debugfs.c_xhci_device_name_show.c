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
struct xhci_virt_device {TYPE_1__* udev; } ;
struct xhci_slot_priv {struct xhci_virt_device* dev; } ;
struct seq_file {struct xhci_slot_priv* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xhci_device_name_show(struct seq_file *s, void *unused)
{
	struct xhci_slot_priv	*priv = s->private;
	struct xhci_virt_device	*dev = priv->dev;

	seq_printf(s, "%s\n", dev_name(&dev->udev->dev));

	return 0;
}