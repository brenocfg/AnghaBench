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
struct hid_device {int debug; int /*<<< orphan*/  debug_dir; void* debug_events; void* debug_rdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hid_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_debug_events_fops ; 
 int /*<<< orphan*/  hid_debug_rdesc_fops ; 
 int /*<<< orphan*/  hid_debug_root ; 

void hid_debug_register(struct hid_device *hdev, const char *name)
{
	hdev->debug_dir = debugfs_create_dir(name, hid_debug_root);
	hdev->debug_rdesc = debugfs_create_file("rdesc", 0400,
			hdev->debug_dir, hdev, &hid_debug_rdesc_fops);
	hdev->debug_events = debugfs_create_file("events", 0400,
			hdev->debug_dir, hdev, &hid_debug_events_fops);
	hdev->debug = 1;
}