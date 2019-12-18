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
struct hid_device {int dummy; } ;
struct dj_receiver_dev {int /*<<< orphan*/  kref; struct hid_device* hidpp; struct hid_device* keyboard; struct hid_device* mouse; } ;

/* Variables and functions */
 int /*<<< orphan*/  dj_hdev_list_lock ; 
 int /*<<< orphan*/  dj_release_receiver_dev ; 
 struct dj_receiver_dev* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dj_put_receiver_dev(struct hid_device *hdev)
{
	struct dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);

	mutex_lock(&dj_hdev_list_lock);

	if (djrcv_dev->mouse == hdev)
		djrcv_dev->mouse = NULL;
	if (djrcv_dev->keyboard == hdev)
		djrcv_dev->keyboard = NULL;
	if (djrcv_dev->hidpp == hdev)
		djrcv_dev->hidpp = NULL;

	kref_put(&djrcv_dev->kref, dj_release_receiver_dev);

	mutex_unlock(&dj_hdev_list_lock);
}