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

/* Variables and functions */
 scalar_t__ IS_ERR (char**) ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  kfree (char**) ; 
 int /*<<< orphan*/  xenbus_check_frontend (char*,char*) ; 
 char** xenbus_directory (int /*<<< orphan*/ ,char*,char*,int*) ; 

__attribute__((used)) static void xenbus_reset_state(void)
{
	char **devclass, **dev;
	int devclass_n, dev_n;
	int i, j;

	devclass = xenbus_directory(XBT_NIL, "device", "", &devclass_n);
	if (IS_ERR(devclass))
		return;

	for (i = 0; i < devclass_n; i++) {
		dev = xenbus_directory(XBT_NIL, "device", devclass[i], &dev_n);
		if (IS_ERR(dev))
			continue;
		for (j = 0; j < dev_n; j++)
			xenbus_check_frontend(devclass[i], dev[j]);
		kfree(dev);
	}
	kfree(devclass);
}