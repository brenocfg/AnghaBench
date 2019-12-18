#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int cn_add_callback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cn_del_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_attr_v86d ; 
 int driver_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fb_get_options (char*,char**) ; 
 int platform_device_add (scalar_t__) ; 
 scalar_t__ platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (scalar_t__) ; 
 int platform_driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_driver_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  uvesafb_cn_callback ; 
 int /*<<< orphan*/  uvesafb_cn_id ; 
 scalar_t__ uvesafb_device ; 
 TYPE_1__ uvesafb_driver ; 
 int /*<<< orphan*/  uvesafb_setup (char*) ; 

__attribute__((used)) static int uvesafb_init(void)
{
	int err;

#ifndef MODULE
	char *option = NULL;

	if (fb_get_options("uvesafb", &option))
		return -ENODEV;
	uvesafb_setup(option);
#endif
	err = cn_add_callback(&uvesafb_cn_id, "uvesafb", uvesafb_cn_callback);
	if (err)
		return err;

	err = platform_driver_register(&uvesafb_driver);

	if (!err) {
		uvesafb_device = platform_device_alloc("uvesafb", 0);
		if (uvesafb_device)
			err = platform_device_add(uvesafb_device);
		else
			err = -ENOMEM;

		if (err) {
			platform_device_put(uvesafb_device);
			platform_driver_unregister(&uvesafb_driver);
			cn_del_callback(&uvesafb_cn_id);
			return err;
		}

		err = driver_create_file(&uvesafb_driver.driver,
				&driver_attr_v86d);
		if (err) {
			pr_warn("failed to register attributes\n");
			err = 0;
		}
	}
	return err;
}