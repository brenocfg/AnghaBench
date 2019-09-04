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
struct m560_private_data {int dummy; } ;
struct hidpp_device {struct m560_private_data* private_data; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct m560_private_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int m560_allocate(struct hid_device *hdev)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);
	struct m560_private_data *d;

	d = devm_kzalloc(&hdev->dev, sizeof(struct m560_private_data),
			GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	hidpp->private_data = d;

	return 0;
}