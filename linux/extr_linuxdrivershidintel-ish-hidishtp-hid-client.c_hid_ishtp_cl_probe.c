#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ishtp_cl_device {struct ishtp_cl* driver_data; int /*<<< orphan*/  ishtp_dev; int /*<<< orphan*/  dev; TYPE_2__* fw_client; } ;
struct ishtp_cl_data {int /*<<< orphan*/  work; int /*<<< orphan*/  ishtp_resume_wait; int /*<<< orphan*/  init_wait; struct ishtp_cl_device* cl_device; struct ishtp_cl* hid_ishtp_cl; } ;
struct ishtp_cl {struct ishtp_cl_data* client_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  protocol_name; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ishtp_cl_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hid_ishtp_cl_init (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_ishtp_cl_reset_handler ; 
 int /*<<< orphan*/  hid_ishtp_guid ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ishtp_cl* ishtp_cl_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_cl_free (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_get_device (struct ishtp_cl_device*) ; 
 scalar_t__ uuid_le_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_ishtp_cl_probe(struct ishtp_cl_device *cl_device)
{
	struct ishtp_cl *hid_ishtp_cl;
	struct ishtp_cl_data *client_data;
	int rv;

	if (!cl_device)
		return	-ENODEV;

	if (uuid_le_cmp(hid_ishtp_guid,
			cl_device->fw_client->props.protocol_name) != 0)
		return	-ENODEV;

	client_data = devm_kzalloc(&cl_device->dev, sizeof(*client_data),
				   GFP_KERNEL);
	if (!client_data)
		return -ENOMEM;

	hid_ishtp_cl = ishtp_cl_allocate(cl_device->ishtp_dev);
	if (!hid_ishtp_cl)
		return -ENOMEM;

	cl_device->driver_data = hid_ishtp_cl;
	hid_ishtp_cl->client_data = client_data;
	client_data->hid_ishtp_cl = hid_ishtp_cl;
	client_data->cl_device = cl_device;

	init_waitqueue_head(&client_data->init_wait);
	init_waitqueue_head(&client_data->ishtp_resume_wait);

	INIT_WORK(&client_data->work, hid_ishtp_cl_reset_handler);

	rv = hid_ishtp_cl_init(hid_ishtp_cl, 0);
	if (rv) {
		ishtp_cl_free(hid_ishtp_cl);
		return rv;
	}
	ishtp_get_device(cl_device);

	return 0;
}