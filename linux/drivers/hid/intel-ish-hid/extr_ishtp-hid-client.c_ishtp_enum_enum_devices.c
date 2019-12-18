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
struct ishtp_cl_data {int /*<<< orphan*/  num_hid_devices; int /*<<< orphan*/  cl_device; int /*<<< orphan*/  hid_dev_count; int /*<<< orphan*/  hid_devices; int /*<<< orphan*/  enum_devices_done; int /*<<< orphan*/  init_wait; } ;
struct ishtp_cl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;
struct hostif_msg {TYPE_1__ hdr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HOSTIF_DM_ENUM_DEVICES ; 
 int HZ ; 
 int /*<<< orphan*/  cl_data_to_dev (struct ishtp_cl_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ishtp_cl_send (struct ishtp_cl*,unsigned char*,int) ; 
 int /*<<< orphan*/  ishtp_device (int /*<<< orphan*/ ) ; 
 struct ishtp_cl_data* ishtp_get_client_data (struct ishtp_cl*) ; 
 int /*<<< orphan*/  memset (struct hostif_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ishtp_enum_enum_devices(struct ishtp_cl *hid_ishtp_cl)
{
	struct hostif_msg msg;
	struct ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);
	int retry_count;
	int rv;

	/* Send HOSTIF_DM_ENUM_DEVICES */
	memset(&msg, 0, sizeof(struct hostif_msg));
	msg.hdr.command = HOSTIF_DM_ENUM_DEVICES;
	rv = ishtp_cl_send(hid_ishtp_cl, (unsigned char *)&msg,
			   sizeof(struct hostif_msg));
	if (rv)
		return rv;

	retry_count = 0;
	while (!client_data->enum_devices_done &&
	       retry_count < 10) {
		wait_event_interruptible_timeout(client_data->init_wait,
					 client_data->enum_devices_done,
					 3 * HZ);
		++retry_count;
		if (!client_data->enum_devices_done)
			/* Send HOSTIF_DM_ENUM_DEVICES */
			rv = ishtp_cl_send(hid_ishtp_cl,
					   (unsigned char *) &msg,
					   sizeof(struct hostif_msg));
	}
	if (!client_data->enum_devices_done) {
		dev_err(cl_data_to_dev(client_data),
			"[hid-ish]: timed out waiting for enum_devices\n");
		return -ETIMEDOUT;
	}
	if (!client_data->hid_devices) {
		dev_err(cl_data_to_dev(client_data),
			"[hid-ish]: failed to allocate HID dev structures\n");
		return -ENOMEM;
	}

	client_data->num_hid_devices = client_data->hid_dev_count;
	dev_info(ishtp_device(client_data->cl_device),
		"[hid-ish]: enum_devices_done OK, num_hid_devices=%d\n",
		client_data->num_hid_devices);

	return	0;
}