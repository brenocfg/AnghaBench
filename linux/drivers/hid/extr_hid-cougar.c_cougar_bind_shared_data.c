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
struct hid_device {int /*<<< orphan*/  dev; } ;
struct cougar_shared {int /*<<< orphan*/  list; struct hid_device* dev; int /*<<< orphan*/  kref; } ;
struct cougar {struct cougar_shared* shared; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cougar_shared* cougar_get_shared_data (struct hid_device*) ; 
 int /*<<< orphan*/  cougar_remove_shared_data (struct cougar*) ; 
 int /*<<< orphan*/  cougar_udev_list ; 
 int /*<<< orphan*/  cougar_udev_list_lock ; 
 int devm_add_action (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct cougar*),struct cougar*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct cougar_shared* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cougar_bind_shared_data(struct hid_device *hdev,
				   struct cougar *cougar)
{
	struct cougar_shared *shared;
	int error = 0;

	mutex_lock(&cougar_udev_list_lock);

	shared = cougar_get_shared_data(hdev);
	if (!shared) {
		shared = kzalloc(sizeof(*shared), GFP_KERNEL);
		if (!shared) {
			error = -ENOMEM;
			goto out;
		}

		kref_init(&shared->kref);
		shared->dev = hdev;
		list_add_tail(&shared->list, &cougar_udev_list);
	}

	cougar->shared = shared;

	error = devm_add_action(&hdev->dev, cougar_remove_shared_data, cougar);
	if (error) {
		mutex_unlock(&cougar_udev_list_lock);
		cougar_remove_shared_data(cougar);
		return error;
	}

out:
	mutex_unlock(&cougar_udev_list_lock);
	return error;
}