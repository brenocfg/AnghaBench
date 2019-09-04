#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ishtp_cl_data {int hid_descr_done; TYPE_3__* cl_device; int /*<<< orphan*/ * hid_descr; int /*<<< orphan*/  init_wait; TYPE_2__* hid_devices; } ;
struct ishtp_cl {struct ishtp_cl_data* client_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  command; } ;
struct hostif_msg {TYPE_1__ hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HOSTIF_GET_HID_DESCRIPTOR ; 
 int HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ishtp_cl_send (struct ishtp_cl*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (struct hostif_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ishtp_get_hid_descriptor(struct ishtp_cl *hid_ishtp_cl, int index)
{
	struct hostif_msg msg;
	struct ishtp_cl_data *client_data = hid_ishtp_cl->client_data;
	int rv;

	/* Get HID descriptor */
	client_data->hid_descr_done = false;
	memset(&msg, 0, sizeof(struct hostif_msg));
	msg.hdr.command = HOSTIF_GET_HID_DESCRIPTOR;
	msg.hdr.device_id = client_data->hid_devices[index].dev_id;
	rv = ishtp_cl_send(hid_ishtp_cl, (unsigned char *) &msg,
			   sizeof(struct hostif_msg));
	if (rv)
		return rv;

	if (!client_data->hid_descr_done) {
		wait_event_interruptible_timeout(client_data->init_wait,
						 client_data->hid_descr_done,
						 3 * HZ);
		if (!client_data->hid_descr_done) {
			dev_err(&client_data->cl_device->dev,
				"[hid-ish]: timed out for hid_descr_done\n");
			return -EIO;
		}

		if (!client_data->hid_descr[index]) {
			dev_err(&client_data->cl_device->dev,
				"[hid-ish]: allocation HID desc fail\n");
			return -ENOMEM;
		}
	}

	return 0;
}