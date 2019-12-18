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
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  hkey_handle ; 
 int kbdlight_brightness ; 
 int /*<<< orphan*/  kbdlight_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kbdlight_set_level(int level)
{
	int ret = 0;

	if (!hkey_handle)
		return -ENXIO;

	mutex_lock(&kbdlight_mutex);

	if (!acpi_evalf(hkey_handle, NULL, "MLCS", "dd", level))
		ret = -EIO;
	else
		kbdlight_brightness = level;

	mutex_unlock(&kbdlight_mutex);

	return ret;
}