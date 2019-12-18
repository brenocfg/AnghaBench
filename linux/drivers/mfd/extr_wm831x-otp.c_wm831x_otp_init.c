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
typedef  int /*<<< orphan*/  uuid ;
struct wm831x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int WM831X_UNIQUE_ID_LEN ; 
 int /*<<< orphan*/  add_device_randomness (char*,int) ; 
 int /*<<< orphan*/  dev_attr_unique_id ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wm831x_unique_id_read (struct wm831x*,char*) ; 

int wm831x_otp_init(struct wm831x *wm831x)
{
	char uuid[WM831X_UNIQUE_ID_LEN];
	int ret;

	ret = device_create_file(wm831x->dev, &dev_attr_unique_id);
	if (ret != 0)
		dev_err(wm831x->dev, "Unique ID attribute not created: %d\n",
			ret);

	ret = wm831x_unique_id_read(wm831x, uuid);
	if (ret == 0)
		add_device_randomness(uuid, sizeof(uuid));
	else
		dev_err(wm831x->dev, "Failed to read UUID: %d\n", ret);

	return ret;
}