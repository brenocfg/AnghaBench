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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct urb {int /*<<< orphan*/  status; struct usb_device* dev; struct s2255_fw* context; } ;
struct s2255_fw {int fw_loaded; int fw_size; int /*<<< orphan*/  fw_state; int /*<<< orphan*/  wait_fw; int /*<<< orphan*/ * fw_urb; int /*<<< orphan*/  pfw_data; TYPE_1__* fw; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int CHUNK_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  S2255_FW_FAILED ; 
 int /*<<< orphan*/  S2255_FW_LOADED_DSPWAIT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s2255_dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void (*) (struct urb*),struct s2255_fw*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s2255_fwchunk_complete(struct urb *urb)
{
	struct s2255_fw *data = urb->context;
	struct usb_device *udev = urb->dev;
	int len;
	if (urb->status) {
		dev_err(&udev->dev, "URB failed with status %d\n", urb->status);
		atomic_set(&data->fw_state, S2255_FW_FAILED);
		/* wake up anything waiting for the firmware */
		wake_up(&data->wait_fw);
		return;
	}
	if (data->fw_urb == NULL) {
		s2255_dev_err(&udev->dev, "disconnected\n");
		atomic_set(&data->fw_state, S2255_FW_FAILED);
		/* wake up anything waiting for the firmware */
		wake_up(&data->wait_fw);
		return;
	}
#define CHUNK_SIZE 512
	/* all USB transfers must be done with continuous kernel memory.
	   can't allocate more than 128k in current linux kernel, so
	   upload the firmware in chunks
	 */
	if (data->fw_loaded < data->fw_size) {
		len = (data->fw_loaded + CHUNK_SIZE) > data->fw_size ?
		    data->fw_size % CHUNK_SIZE : CHUNK_SIZE;

		if (len < CHUNK_SIZE)
			memset(data->pfw_data, 0, CHUNK_SIZE);

		memcpy(data->pfw_data,
		       (char *) data->fw->data + data->fw_loaded, len);

		usb_fill_bulk_urb(data->fw_urb, udev, usb_sndbulkpipe(udev, 2),
				  data->pfw_data, CHUNK_SIZE,
				  s2255_fwchunk_complete, data);
		if (usb_submit_urb(data->fw_urb, GFP_ATOMIC) < 0) {
			dev_err(&udev->dev, "failed submit URB\n");
			atomic_set(&data->fw_state, S2255_FW_FAILED);
			/* wake up anything waiting for the firmware */
			wake_up(&data->wait_fw);
			return;
		}
		data->fw_loaded += len;
	} else
		atomic_set(&data->fw_state, S2255_FW_LOADED_DSPWAIT);
	return;

}