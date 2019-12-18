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
struct seq_file {struct hid_device* private; } ;
struct hid_device {unsigned int rsize; unsigned int dev_rsize; int /*<<< orphan*/  driver_input_lock; int /*<<< orphan*/ * dev_rdesc; int /*<<< orphan*/ * rdesc; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_dump_device (struct hid_device*,struct seq_file*) ; 
 int /*<<< orphan*/  hid_dump_input_mapping (struct hid_device*,struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hid_debug_rdesc_show(struct seq_file *f, void *p)
{
	struct hid_device *hdev = f->private;
	const __u8 *rdesc = hdev->rdesc;
	unsigned rsize = hdev->rsize;
	int i;

	if (!rdesc) {
		rdesc = hdev->dev_rdesc;
		rsize = hdev->dev_rsize;
	}

	/* dump HID report descriptor */
	for (i = 0; i < rsize; i++)
		seq_printf(f, "%02x ", rdesc[i]);
	seq_printf(f, "\n\n");

	/* dump parsed data and input mappings */
	if (down_interruptible(&hdev->driver_input_lock))
		return 0;

	hid_dump_device(hdev, f);
	seq_printf(f, "\n");
	hid_dump_input_mapping(hdev, f);

	up(&hdev->driver_input_lock);

	return 0;
}