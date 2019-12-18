#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  release; } ;
struct hsi_port {unsigned int num; TYPE_1__ device; int /*<<< orphan*/  n_head; int /*<<< orphan*/  lock; void* release; void* stop_tx; void* start_tx; void* flush; void* setup; int /*<<< orphan*/  async; } ;
struct hsi_controller {unsigned int num_ports; struct hsi_port** port; TYPE_1__ device; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,unsigned int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  hsi_controller_release ; 
 void* hsi_dummy_cl ; 
 int /*<<< orphan*/  hsi_dummy_msg ; 
 int /*<<< orphan*/  hsi_port_release ; 
 int /*<<< orphan*/  hsi_put_controller (struct hsi_controller*) ; 
 struct hsi_port** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hsi_controller*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct hsi_controller *hsi_alloc_controller(unsigned int n_ports, gfp_t flags)
{
	struct hsi_controller	*hsi;
	struct hsi_port		**port;
	unsigned int		i;

	if (!n_ports)
		return NULL;

	hsi = kzalloc(sizeof(*hsi), flags);
	if (!hsi)
		return NULL;
	port = kcalloc(n_ports, sizeof(*port), flags);
	if (!port) {
		kfree(hsi);
		return NULL;
	}
	hsi->num_ports = n_ports;
	hsi->port = port;
	hsi->device.release = hsi_controller_release;
	device_initialize(&hsi->device);

	for (i = 0; i < n_ports; i++) {
		port[i] = kzalloc(sizeof(**port), flags);
		if (port[i] == NULL)
			goto out;
		port[i]->num = i;
		port[i]->async = hsi_dummy_msg;
		port[i]->setup = hsi_dummy_cl;
		port[i]->flush = hsi_dummy_cl;
		port[i]->start_tx = hsi_dummy_cl;
		port[i]->stop_tx = hsi_dummy_cl;
		port[i]->release = hsi_dummy_cl;
		mutex_init(&port[i]->lock);
		BLOCKING_INIT_NOTIFIER_HEAD(&port[i]->n_head);
		dev_set_name(&port[i]->device, "port%d", i);
		hsi->port[i]->device.release = hsi_port_release;
		device_initialize(&hsi->port[i]->device);
	}

	return hsi;
out:
	hsi_put_controller(hsi);

	return NULL;
}