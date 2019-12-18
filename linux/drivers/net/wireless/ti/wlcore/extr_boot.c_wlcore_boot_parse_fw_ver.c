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
struct wl1271_static_data {int /*<<< orphan*/  fw_version; } ;
struct TYPE_2__ {char* fw_ver_str; int /*<<< orphan*/ * fw_ver; } ;
struct wl1271 {TYPE_1__ chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 
 int wlcore_identify_fw (struct wl1271*) ; 

__attribute__((used)) static int wlcore_boot_parse_fw_ver(struct wl1271 *wl,
				    struct wl1271_static_data *static_data)
{
	int ret;

	strncpy(wl->chip.fw_ver_str, static_data->fw_version,
		sizeof(wl->chip.fw_ver_str));

	/* make sure the string is NULL-terminated */
	wl->chip.fw_ver_str[sizeof(wl->chip.fw_ver_str) - 1] = '\0';

	ret = sscanf(wl->chip.fw_ver_str + 4, "%u.%u.%u.%u.%u",
		     &wl->chip.fw_ver[0], &wl->chip.fw_ver[1],
		     &wl->chip.fw_ver[2], &wl->chip.fw_ver[3],
		     &wl->chip.fw_ver[4]);

	if (ret != 5) {
		wl1271_warning("fw version incorrect value");
		memset(wl->chip.fw_ver, 0, sizeof(wl->chip.fw_ver));
		ret = -EINVAL;
		goto out;
	}

	ret = wlcore_identify_fw(wl);
	if (ret < 0)
		goto out;
out:
	return ret;
}