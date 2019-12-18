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
struct pcmcia_socket {int /*<<< orphan*/  present; scalar_t__ device_count; scalar_t__ pcmcia_pfc; int /*<<< orphan*/  devices_list; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct class_interface {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pcmcia_socket* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pccard_cis_attr ; 
 int pccard_register_pcmcia (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_bus_callback ; 
 struct pcmcia_socket* pcmcia_get_socket (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  pcmcia_put_socket (struct pcmcia_socket*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcmcia_bus_add_socket(struct device *dev,
					   struct class_interface *class_intf)
{
	struct pcmcia_socket *socket = dev_get_drvdata(dev);
	int ret;

	socket = pcmcia_get_socket(socket);
	if (!socket) {
		dev_err(dev, "PCMCIA obtaining reference to socket failed\n");
		return -ENODEV;
	}

	ret = sysfs_create_bin_file(&dev->kobj, &pccard_cis_attr);
	if (ret) {
		dev_err(dev, "PCMCIA registration failed\n");
		pcmcia_put_socket(socket);
		return ret;
	}

	INIT_LIST_HEAD(&socket->devices_list);
	socket->pcmcia_pfc = 0;
	socket->device_count = 0;
	atomic_set(&socket->present, 0);

	ret = pccard_register_pcmcia(socket, &pcmcia_bus_callback);
	if (ret) {
		dev_err(dev, "PCMCIA registration failed\n");
		pcmcia_put_socket(socket);
		return ret;
	}

	return 0;
}