#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sensor_hub_data {size_t hid_sensor_client_cnt; TYPE_1__* hid_sensor_hub_client_devs; int /*<<< orphan*/  dyn_callback_list; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dyn_callback_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  quirks; } ;
struct mutex {int dummy; } ;
struct mfd_cell {int dummy; } ;
struct hid_sensor_hub_device {scalar_t__ usage; int start_collection_index; int end_collection_index; int /*<<< orphan*/ * mutex_ptr; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; struct hid_device* hdev; } ;
struct hid_device_id {int /*<<< orphan*/  driver_data; } ;
struct hid_device {int maxcollection; int /*<<< orphan*/  dev; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; struct hid_collection* collection; int /*<<< orphan*/  inputs; } ;
struct hid_collection {scalar_t__ type; scalar_t__ usage; } ;
struct TYPE_3__ {char* name; int pdata_size; struct hid_sensor_hub_device* platform_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HID_COLLECTION_APPLICATION ; 
 scalar_t__ HID_COLLECTION_PHYSICAL ; 
 int HID_MAX_PHY_DEVICES ; 
 scalar_t__ HID_USAGE_SENSOR_COLLECTION ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 char* devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_1__* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,char*,int) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct sensor_hub_data*) ; 
 int mfd_add_hotplug_devices (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sensor_hub_get_physical_device_count (struct hid_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sensor_hub_probe(struct hid_device *hdev,
				const struct hid_device_id *id)
{
	int ret;
	struct sensor_hub_data *sd;
	int i;
	char *name;
	int dev_cnt;
	struct hid_sensor_hub_device *hsdev;
	struct hid_sensor_hub_device *last_hsdev = NULL;
	struct hid_sensor_hub_device *collection_hsdev = NULL;

	sd = devm_kzalloc(&hdev->dev, sizeof(*sd), GFP_KERNEL);
	if (!sd) {
		hid_err(hdev, "cannot allocate Sensor data\n");
		return -ENOMEM;
	}

	hid_set_drvdata(hdev, sd);
	sd->quirks = id->driver_data;

	spin_lock_init(&sd->lock);
	spin_lock_init(&sd->dyn_callback_lock);
	mutex_init(&sd->mutex);
	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		return ret;
	}
	INIT_LIST_HEAD(&hdev->inputs);

	ret = hid_hw_start(hdev, 0);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		return ret;
	}
	INIT_LIST_HEAD(&sd->dyn_callback_list);
	sd->hid_sensor_client_cnt = 0;

	dev_cnt = sensor_hub_get_physical_device_count(hdev);
	if (dev_cnt > HID_MAX_PHY_DEVICES) {
		hid_err(hdev, "Invalid Physical device count\n");
		ret = -EINVAL;
		goto err_stop_hw;
	}
	sd->hid_sensor_hub_client_devs = devm_kcalloc(&hdev->dev,
						      dev_cnt,
						      sizeof(struct mfd_cell),
						      GFP_KERNEL);
	if (sd->hid_sensor_hub_client_devs == NULL) {
		hid_err(hdev, "Failed to allocate memory for mfd cells\n");
		ret = -ENOMEM;
		goto err_stop_hw;
	}

	for (i = 0; i < hdev->maxcollection; ++i) {
		struct hid_collection *collection = &hdev->collection[i];

		if (collection->type == HID_COLLECTION_PHYSICAL ||
		    collection->type == HID_COLLECTION_APPLICATION) {

			hsdev = devm_kzalloc(&hdev->dev, sizeof(*hsdev),
					     GFP_KERNEL);
			if (!hsdev) {
				hid_err(hdev, "cannot allocate hid_sensor_hub_device\n");
				ret = -ENOMEM;
				goto err_stop_hw;
			}
			hsdev->hdev = hdev;
			hsdev->vendor_id = hdev->vendor;
			hsdev->product_id = hdev->product;
			hsdev->usage = collection->usage;
			hsdev->mutex_ptr = devm_kzalloc(&hdev->dev,
							sizeof(struct mutex),
							GFP_KERNEL);
			if (!hsdev->mutex_ptr) {
				ret = -ENOMEM;
				goto err_stop_hw;
			}
			mutex_init(hsdev->mutex_ptr);
			hsdev->start_collection_index = i;
			if (last_hsdev)
				last_hsdev->end_collection_index = i;
			last_hsdev = hsdev;
			name = devm_kasprintf(&hdev->dev, GFP_KERNEL,
					      "HID-SENSOR-%x",
					      collection->usage);
			if (name == NULL) {
				hid_err(hdev, "Failed MFD device name\n");
				ret = -ENOMEM;
				goto err_stop_hw;
			}
			sd->hid_sensor_hub_client_devs[
				sd->hid_sensor_client_cnt].name = name;
			sd->hid_sensor_hub_client_devs[
				sd->hid_sensor_client_cnt].platform_data =
							hsdev;
			sd->hid_sensor_hub_client_devs[
				sd->hid_sensor_client_cnt].pdata_size =
							sizeof(*hsdev);
			hid_dbg(hdev, "Adding %s:%d\n", name,
					hsdev->start_collection_index);
			sd->hid_sensor_client_cnt++;
			if (collection_hsdev)
				collection_hsdev->end_collection_index = i;
			if (collection->type == HID_COLLECTION_APPLICATION &&
			    collection->usage == HID_USAGE_SENSOR_COLLECTION)
				collection_hsdev = hsdev;
		}
	}
	if (last_hsdev)
		last_hsdev->end_collection_index = i;
	if (collection_hsdev)
		collection_hsdev->end_collection_index = i;

	ret = mfd_add_hotplug_devices(&hdev->dev,
			sd->hid_sensor_hub_client_devs,
			sd->hid_sensor_client_cnt);
	if (ret < 0)
		goto err_stop_hw;

	return ret;

err_stop_hw:
	hid_hw_stop(hdev);

	return ret;
}