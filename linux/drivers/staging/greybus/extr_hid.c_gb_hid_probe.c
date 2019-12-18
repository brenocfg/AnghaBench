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
struct hid_device {int dummy; } ;
struct greybus_descriptor_cport {scalar_t__ protocol_id; int /*<<< orphan*/  id; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_hid {struct gb_bundle* bundle; struct hid_device* hid; struct hid_device* connection; } ;
typedef  struct hid_device gb_connection ;
struct gb_bundle {int num_cports; struct greybus_descriptor_cport* cport_desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GREYBUS_PROTOCOL_HID ; 
 scalar_t__ IS_ERR (struct hid_device*) ; 
 int PTR_ERR (struct hid_device*) ; 
 struct hid_device* gb_connection_create (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct hid_device*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct hid_device*) ; 
 int gb_connection_enable (struct hid_device*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct hid_device*,struct gb_hid*) ; 
 int gb_hid_init (struct gb_hid*) ; 
 int /*<<< orphan*/  gb_hid_request_handler ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gb_hid*) ; 
 int hid_add_device (struct hid_device*) ; 
 struct hid_device* hid_allocate_device () ; 
 int /*<<< orphan*/  hid_destroy_device (struct hid_device*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct gb_hid*) ; 
 struct gb_hid* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_hid_probe(struct gb_bundle *bundle,
			const struct greybus_bundle_id *id)
{
	struct greybus_descriptor_cport *cport_desc;
	struct gb_connection *connection;
	struct hid_device *hid;
	struct gb_hid *ghid;
	int ret;

	if (bundle->num_cports != 1)
		return -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	if (cport_desc->protocol_id != GREYBUS_PROTOCOL_HID)
		return -ENODEV;

	ghid = kzalloc(sizeof(*ghid), GFP_KERNEL);
	if (!ghid)
		return -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_hid_request_handler);
	if (IS_ERR(connection)) {
		ret = PTR_ERR(connection);
		goto err_free_ghid;
	}

	gb_connection_set_data(connection, ghid);
	ghid->connection = connection;

	hid = hid_allocate_device();
	if (IS_ERR(hid)) {
		ret = PTR_ERR(hid);
		goto err_connection_destroy;
	}

	ghid->hid = hid;
	ghid->bundle = bundle;

	greybus_set_drvdata(bundle, ghid);

	ret = gb_connection_enable(connection);
	if (ret)
		goto err_destroy_hid;

	ret = gb_hid_init(ghid);
	if (ret)
		goto err_connection_disable;

	ret = hid_add_device(hid);
	if (ret) {
		hid_err(hid, "can't add hid device: %d\n", ret);
		goto err_connection_disable;
	}

	gb_pm_runtime_put_autosuspend(bundle);

	return 0;

err_connection_disable:
	gb_connection_disable(connection);
err_destroy_hid:
	hid_destroy_device(hid);
err_connection_destroy:
	gb_connection_destroy(connection);
err_free_ghid:
	kfree(ghid);

	return ret;
}