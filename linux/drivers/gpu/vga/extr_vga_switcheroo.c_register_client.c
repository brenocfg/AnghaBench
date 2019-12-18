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
struct vga_switcheroo_client_ops {int dummy; } ;
struct vga_switcheroo_client {int id; int active; int driver_power_control; int /*<<< orphan*/  list; struct pci_dev* vga_dev; struct vga_switcheroo_client_ops const* ops; struct pci_dev* pdev; int /*<<< orphan*/  pwr_state; } ;
struct pci_dev {int dummy; } ;
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_2__ {int /*<<< orphan*/  registered_clients; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VGA_SWITCHEROO_ON ; 
 scalar_t__ client_is_vga (struct vga_switcheroo_client*) ; 
 struct vga_switcheroo_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  vga_switcheroo_enable () ; 
 scalar_t__ vga_switcheroo_ready () ; 
 int /*<<< orphan*/  vgasr_mutex ; 
 TYPE_1__ vgasr_priv ; 

__attribute__((used)) static int register_client(struct pci_dev *pdev,
			   const struct vga_switcheroo_client_ops *ops,
			   enum vga_switcheroo_client_id id,
			   struct pci_dev *vga_dev,
			   bool active,
			   bool driver_power_control)
{
	struct vga_switcheroo_client *client;

	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (!client)
		return -ENOMEM;

	client->pwr_state = VGA_SWITCHEROO_ON;
	client->pdev = pdev;
	client->ops = ops;
	client->id = id;
	client->active = active;
	client->driver_power_control = driver_power_control;
	client->vga_dev = vga_dev;

	mutex_lock(&vgasr_mutex);
	list_add_tail(&client->list, &vgasr_priv.clients);
	if (client_is_vga(client))
		vgasr_priv.registered_clients++;

	if (vga_switcheroo_ready()) {
		pr_info("enabled\n");
		vga_switcheroo_enable();
	}
	mutex_unlock(&vgasr_mutex);
	return 0;
}