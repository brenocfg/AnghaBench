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
typedef  int /*<<< orphan*/  u8 ;
struct sony_sc {void* fw_version; void* hw_version; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS4_FEATURE_REPORT_0xA3_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 void* get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int hid_hw_raw_request (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dualshock4_get_version_info(struct sony_sc *sc)
{
	u8 *buf;
	int ret;

	buf = kmalloc(DS4_FEATURE_REPORT_0xA3_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = hid_hw_raw_request(sc->hdev, 0xA3, buf,
				 DS4_FEATURE_REPORT_0xA3_SIZE,
				 HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	if (ret < 0) {
		kfree(buf);
		return ret;
	}

	sc->hw_version = get_unaligned_le16(&buf[35]);
	sc->fw_version = get_unaligned_le16(&buf[41]);

	kfree(buf);
	return 0;
}