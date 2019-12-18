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
struct work_struct {int dummy; } ;
struct sas_discovery_event {struct asd_sas_port* port; } ;
struct domain_device {int dev_type; int /*<<< orphan*/  dev_list_node; int /*<<< orphan*/  disco_list_node; int /*<<< orphan*/  rphy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending; } ;
struct asd_sas_port {int /*<<< orphan*/  id; struct domain_device* port_dev; int /*<<< orphan*/  dev_list_lock; TYPE_1__ disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_DISCOVER_DOMAIN ; 
 int ENXIO ; 
#define  SAS_EDGE_EXPANDER_DEVICE 132 
#define  SAS_END_DEVICE 131 
#define  SAS_FANOUT_EXPANDER_DEVICE 130 
#define  SAS_SATA_DEV 129 
#define  SAS_SATA_PM 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int sas_discover_end_dev (struct domain_device*) ; 
 int sas_discover_root_expander (struct domain_device*) ; 
 int sas_discover_sata (struct domain_device*) ; 
 int sas_get_port_device (struct asd_sas_port*) ; 
 int /*<<< orphan*/  sas_probe_devices (struct asd_sas_port*) ; 
 int /*<<< orphan*/  sas_put_device (struct domain_device*) ; 
 int /*<<< orphan*/  sas_rphy_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 struct sas_discovery_event* to_sas_discovery_event (struct work_struct*) ; 

__attribute__((used)) static void sas_discover_domain(struct work_struct *work)
{
	struct domain_device *dev;
	int error = 0;
	struct sas_discovery_event *ev = to_sas_discovery_event(work);
	struct asd_sas_port *port = ev->port;

	clear_bit(DISCE_DISCOVER_DOMAIN, &port->disc.pending);

	if (port->port_dev)
		return;

	error = sas_get_port_device(port);
	if (error)
		return;
	dev = port->port_dev;

	pr_debug("DOING DISCOVERY on port %d, pid:%d\n", port->id,
		 task_pid_nr(current));

	switch (dev->dev_type) {
	case SAS_END_DEVICE:
		error = sas_discover_end_dev(dev);
		break;
	case SAS_EDGE_EXPANDER_DEVICE:
	case SAS_FANOUT_EXPANDER_DEVICE:
		error = sas_discover_root_expander(dev);
		break;
	case SAS_SATA_DEV:
	case SAS_SATA_PM:
#ifdef CONFIG_SCSI_SAS_ATA
		error = sas_discover_sata(dev);
		break;
#else
		pr_notice("ATA device seen but CONFIG_SCSI_SAS_ATA=N so cannot attach\n");
		/* Fall through */
#endif
		/* Fall through - only for the #else condition above. */
	default:
		error = -ENXIO;
		pr_err("unhandled device %d\n", dev->dev_type);
		break;
	}

	if (error) {
		sas_rphy_free(dev->rphy);
		list_del_init(&dev->disco_list_node);
		spin_lock_irq(&port->dev_list_lock);
		list_del_init(&dev->dev_list_node);
		spin_unlock_irq(&port->dev_list_lock);

		sas_put_device(dev);
		port->port_dev = NULL;
	}

	sas_probe_devices(port);

	pr_debug("DONE DISCOVERY on port %d, pid:%d, result:%d\n", port->id,
		 task_pid_nr(current), error);
}