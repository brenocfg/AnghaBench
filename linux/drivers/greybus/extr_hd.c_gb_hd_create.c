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
struct device {int /*<<< orphan*/  dma_mask; struct device* parent; int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; } ;
struct gb_host_device {int bus_id; size_t buffer_size_max; size_t num_cports; struct device dev; int /*<<< orphan*/  svc; int /*<<< orphan*/  cport_id_map; int /*<<< orphan*/  connections; int /*<<< orphan*/  modules; struct gb_hd_driver* driver; } ;
struct gb_hd_driver {scalar_t__ hd_priv_size; int /*<<< orphan*/  message_cancel; int /*<<< orphan*/  message_send; } ;

/* Variables and functions */
 int CPORT_ID_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct gb_host_device* ERR_PTR (int) ; 
 size_t GB_OPERATION_MESSAGE_SIZE_MAX ; 
 size_t GB_OPERATION_MESSAGE_SIZE_MIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_groups ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,size_t) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  gb_hd_bus_id_map ; 
 int /*<<< orphan*/  gb_svc_create (struct gb_host_device*) ; 
 int /*<<< orphan*/  greybus_bus_type ; 
 int /*<<< orphan*/  greybus_hd_type ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gb_host_device*) ; 
 struct gb_host_device* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  trace_gb_hd_create (struct gb_host_device*) ; 

struct gb_host_device *gb_hd_create(struct gb_hd_driver *driver,
				    struct device *parent,
				    size_t buffer_size_max,
				    size_t num_cports)
{
	struct gb_host_device *hd;
	int ret;

	/*
	 * Validate that the driver implements all of the callbacks
	 * so that we don't have to every time we make them.
	 */
	if ((!driver->message_send) || (!driver->message_cancel)) {
		dev_err(parent, "mandatory hd-callbacks missing\n");
		return ERR_PTR(-EINVAL);
	}

	if (buffer_size_max < GB_OPERATION_MESSAGE_SIZE_MIN) {
		dev_err(parent, "greybus host-device buffers too small\n");
		return ERR_PTR(-EINVAL);
	}

	if (num_cports == 0 || num_cports > CPORT_ID_MAX + 1) {
		dev_err(parent, "Invalid number of CPorts: %zu\n", num_cports);
		return ERR_PTR(-EINVAL);
	}

	/*
	 * Make sure to never allocate messages larger than what the Greybus
	 * protocol supports.
	 */
	if (buffer_size_max > GB_OPERATION_MESSAGE_SIZE_MAX) {
		dev_warn(parent, "limiting buffer size to %u\n",
			 GB_OPERATION_MESSAGE_SIZE_MAX);
		buffer_size_max = GB_OPERATION_MESSAGE_SIZE_MAX;
	}

	hd = kzalloc(sizeof(*hd) + driver->hd_priv_size, GFP_KERNEL);
	if (!hd)
		return ERR_PTR(-ENOMEM);

	ret = ida_simple_get(&gb_hd_bus_id_map, 1, 0, GFP_KERNEL);
	if (ret < 0) {
		kfree(hd);
		return ERR_PTR(ret);
	}
	hd->bus_id = ret;

	hd->driver = driver;
	INIT_LIST_HEAD(&hd->modules);
	INIT_LIST_HEAD(&hd->connections);
	ida_init(&hd->cport_id_map);
	hd->buffer_size_max = buffer_size_max;
	hd->num_cports = num_cports;

	hd->dev.parent = parent;
	hd->dev.bus = &greybus_bus_type;
	hd->dev.type = &greybus_hd_type;
	hd->dev.groups = bus_groups;
	hd->dev.dma_mask = hd->dev.parent->dma_mask;
	device_initialize(&hd->dev);
	dev_set_name(&hd->dev, "greybus%d", hd->bus_id);

	trace_gb_hd_create(hd);

	hd->svc = gb_svc_create(hd);
	if (!hd->svc) {
		dev_err(&hd->dev, "failed to create svc\n");
		put_device(&hd->dev);
		return ERR_PTR(-ENOMEM);
	}

	return hd;
}