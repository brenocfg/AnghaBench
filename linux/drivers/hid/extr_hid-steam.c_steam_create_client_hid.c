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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct hid_device {int /*<<< orphan*/  group; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  country; int /*<<< orphan*/  type; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bus; TYPE_1__ dev; int /*<<< orphan*/ * ll_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_GROUP_STEAM ; 
 scalar_t__ IS_ERR (struct hid_device*) ; 
 struct hid_device* hid_allocate_device () ; 
 int /*<<< orphan*/  steam_client_ll_driver ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct hid_device *steam_create_client_hid(struct hid_device *hdev)
{
	struct hid_device *client_hdev;

	client_hdev = hid_allocate_device();
	if (IS_ERR(client_hdev))
		return client_hdev;

	client_hdev->ll_driver = &steam_client_ll_driver;
	client_hdev->dev.parent = hdev->dev.parent;
	client_hdev->bus = hdev->bus;
	client_hdev->vendor = hdev->vendor;
	client_hdev->product = hdev->product;
	client_hdev->version = hdev->version;
	client_hdev->type = hdev->type;
	client_hdev->country = hdev->country;
	strlcpy(client_hdev->name, hdev->name,
			sizeof(client_hdev->name));
	strlcpy(client_hdev->phys, hdev->phys,
			sizeof(client_hdev->phys));
	/*
	 * Since we use the same device info than the real interface to
	 * trick userspace, we will be calling steam_probe recursively.
	 * We need to recognize the client interface somehow.
	 */
	client_hdev->group = HID_GROUP_STEAM;
	return client_hdev;
}