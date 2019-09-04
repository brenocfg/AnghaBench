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
struct k400_private_data {int dummy; } ;
struct hidpp_device {struct k400_private_data* private_data; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct k400_private_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int k400_allocate(struct hid_device *hdev)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);
	struct k400_private_data *k400;

	k400 = devm_kzalloc(&hdev->dev, sizeof(struct k400_private_data),
			    GFP_KERNEL);
	if (!k400)
		return -ENOMEM;

	hidpp->private_data = k400;

	return 0;
}