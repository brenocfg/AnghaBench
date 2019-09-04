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
struct s2255_dev {int /*<<< orphan*/  timer; TYPE_2__* fw_data; int /*<<< orphan*/  udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  pfw_data; int /*<<< orphan*/  fw_urb; int /*<<< orphan*/  fw_loaded; TYPE_1__* fw; int /*<<< orphan*/  fw_state; int /*<<< orphan*/  fw_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_SIZE ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  S2255_FW_NOTLOADED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  s2255_fwchunk_complete ; 
 int /*<<< orphan*/  s2255_reset_dsppower (struct s2255_dev*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s2255_fwload_start(struct s2255_dev *dev)
{
	s2255_reset_dsppower(dev);
	dev->fw_data->fw_size = dev->fw_data->fw->size;
	atomic_set(&dev->fw_data->fw_state, S2255_FW_NOTLOADED);
	memcpy(dev->fw_data->pfw_data,
	       dev->fw_data->fw->data, CHUNK_SIZE);
	dev->fw_data->fw_loaded = CHUNK_SIZE;
	usb_fill_bulk_urb(dev->fw_data->fw_urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, 2),
			  dev->fw_data->pfw_data,
			  CHUNK_SIZE, s2255_fwchunk_complete,
			  dev->fw_data);
	mod_timer(&dev->timer, jiffies + HZ);
}