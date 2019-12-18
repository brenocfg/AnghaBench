#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* parent; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; } ;
struct gb_svc {TYPE_1__ dev; int /*<<< orphan*/  connection; struct gb_host_device* hd; int /*<<< orphan*/  state; int /*<<< orphan*/  device_id_map; int /*<<< orphan*/  wq; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_mask; } ;
struct gb_host_device {int /*<<< orphan*/  bus_id; TYPE_4__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_CPORT_ID ; 
 int /*<<< orphan*/  GB_SVC_STATE_RESET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  gb_connection_create_static (struct gb_host_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_set_data (int /*<<< orphan*/ ,struct gb_svc*) ; 
 int /*<<< orphan*/  gb_svc_request_handler ; 
 int /*<<< orphan*/  greybus_bus_type ; 
 int /*<<< orphan*/  greybus_svc_type ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gb_svc*) ; 
 struct gb_svc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  svc_groups ; 

struct gb_svc *gb_svc_create(struct gb_host_device *hd)
{
	struct gb_svc *svc;

	svc = kzalloc(sizeof(*svc), GFP_KERNEL);
	if (!svc)
		return NULL;

	svc->wq = alloc_workqueue("%s:svc", WQ_UNBOUND, 1, dev_name(&hd->dev));
	if (!svc->wq) {
		kfree(svc);
		return NULL;
	}

	svc->dev.parent = &hd->dev;
	svc->dev.bus = &greybus_bus_type;
	svc->dev.type = &greybus_svc_type;
	svc->dev.groups = svc_groups;
	svc->dev.dma_mask = svc->dev.parent->dma_mask;
	device_initialize(&svc->dev);

	dev_set_name(&svc->dev, "%d-svc", hd->bus_id);

	ida_init(&svc->device_id_map);
	svc->state = GB_SVC_STATE_RESET;
	svc->hd = hd;

	svc->connection = gb_connection_create_static(hd, GB_SVC_CPORT_ID,
						      gb_svc_request_handler);
	if (IS_ERR(svc->connection)) {
		dev_err(&svc->dev, "failed to create connection: %ld\n",
			PTR_ERR(svc->connection));
		goto err_put_device;
	}

	gb_connection_set_data(svc->connection, svc);

	return svc;

err_put_device:
	put_device(&svc->dev);
	return NULL;
}