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
struct greybus_descriptor_cport {scalar_t__ protocol_id; int /*<<< orphan*/  id; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_raw {int /*<<< orphan*/  cdev; struct gb_connection* device; int /*<<< orphan*/  dev; struct gb_connection* connection; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  list; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct gb_bundle {int num_cports; struct greybus_descriptor_cport* cport_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GREYBUS_PROTOCOL_RAW ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct gb_connection* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_raw*,char*,int) ; 
 struct gb_connection* gb_connection_create (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_raw_request_handler ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gb_raw*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct gb_raw*) ; 
 struct gb_raw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minors ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_class ; 
 int /*<<< orphan*/  raw_fops ; 
 int /*<<< orphan*/  raw_major ; 

__attribute__((used)) static int gb_raw_probe(struct gb_bundle *bundle,
			const struct greybus_bundle_id *id)
{
	struct greybus_descriptor_cport *cport_desc;
	struct gb_connection *connection;
	struct gb_raw *raw;
	int retval;
	int minor;

	if (bundle->num_cports != 1)
		return -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	if (cport_desc->protocol_id != GREYBUS_PROTOCOL_RAW)
		return -ENODEV;

	raw = kzalloc(sizeof(*raw), GFP_KERNEL);
	if (!raw)
		return -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_raw_request_handler);
	if (IS_ERR(connection)) {
		retval = PTR_ERR(connection);
		goto error_free;
	}

	INIT_LIST_HEAD(&raw->list);
	mutex_init(&raw->list_lock);

	raw->connection = connection;
	greybus_set_drvdata(bundle, raw);

	minor = ida_simple_get(&minors, 0, 0, GFP_KERNEL);
	if (minor < 0) {
		retval = minor;
		goto error_connection_destroy;
	}

	raw->dev = MKDEV(raw_major, minor);
	cdev_init(&raw->cdev, &raw_fops);

	retval = gb_connection_enable(connection);
	if (retval)
		goto error_remove_ida;

	retval = cdev_add(&raw->cdev, raw->dev, 1);
	if (retval)
		goto error_connection_disable;

	raw->device = device_create(raw_class, &connection->bundle->dev,
				    raw->dev, raw, "gb!raw%d", minor);
	if (IS_ERR(raw->device)) {
		retval = PTR_ERR(raw->device);
		goto error_del_cdev;
	}

	return 0;

error_del_cdev:
	cdev_del(&raw->cdev);

error_connection_disable:
	gb_connection_disable(connection);

error_remove_ida:
	ida_simple_remove(&minors, minor);

error_connection_destroy:
	gb_connection_destroy(connection);

error_free:
	kfree(raw);
	return retval;
}