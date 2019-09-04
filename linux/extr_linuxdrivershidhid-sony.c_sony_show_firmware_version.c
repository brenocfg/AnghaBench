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
struct sony_sc {int fw_version; } ;
struct hid_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct sony_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t sony_show_firmware_version(struct device *dev,
				struct device_attribute
				*attr, char *buf)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct sony_sc *sc = hid_get_drvdata(hdev);

	return snprintf(buf, PAGE_SIZE, "0x%04x\n", sc->fw_version);
}