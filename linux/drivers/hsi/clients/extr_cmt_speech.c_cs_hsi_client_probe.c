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
struct hsi_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int channel_id_cmd; int channel_id_data; int /*<<< orphan*/  dataind_queue; int /*<<< orphan*/  chardev_queue; int /*<<< orphan*/ * hi; struct hsi_client* cl; scalar_t__ opened; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__ cs_char_data ; 
 int /*<<< orphan*/  cs_char_miscdev ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* hsi_get_channel_id_by_name (struct hsi_client*,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct hsi_client* to_hsi_client (struct device*) ; 

__attribute__((used)) static int cs_hsi_client_probe(struct device *dev)
{
	int err = 0;
	struct hsi_client *cl = to_hsi_client(dev);

	dev_dbg(dev, "hsi_client_probe\n");
	init_waitqueue_head(&cs_char_data.wait);
	spin_lock_init(&cs_char_data.lock);
	cs_char_data.opened = 0;
	cs_char_data.cl = cl;
	cs_char_data.hi = NULL;
	INIT_LIST_HEAD(&cs_char_data.chardev_queue);
	INIT_LIST_HEAD(&cs_char_data.dataind_queue);

	cs_char_data.channel_id_cmd = hsi_get_channel_id_by_name(cl,
		"speech-control");
	if (cs_char_data.channel_id_cmd < 0) {
		err = cs_char_data.channel_id_cmd;
		dev_err(dev, "Could not get cmd channel (%d)\n", err);
		return err;
	}

	cs_char_data.channel_id_data = hsi_get_channel_id_by_name(cl,
		"speech-data");
	if (cs_char_data.channel_id_data < 0) {
		err = cs_char_data.channel_id_data;
		dev_err(dev, "Could not get data channel (%d)\n", err);
		return err;
	}

	err = misc_register(&cs_char_miscdev);
	if (err)
		dev_err(dev, "Failed to register: %d\n", err);

	return err;
}