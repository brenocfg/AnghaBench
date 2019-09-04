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
typedef  int u8 ;
struct saitek_sc {int quirks; int mode; } ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int SAITEK_RELEASE_MODE_MMO7 ; 
 int SAITEK_RELEASE_MODE_RAT7 ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,int) ; 
 struct saitek_sc* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int saitek_raw_event(struct hid_device *hdev,
		struct hid_report *report, u8 *raw_data, int size)
{
	struct saitek_sc *ssc = hid_get_drvdata(hdev);

	if (ssc->quirks & SAITEK_RELEASE_MODE_RAT7 && size == 7) {
		/* R.A.T.7 uses bits 13, 14, 15 for the mode */
		int mode = -1;
		if (raw_data[1] & 0x01)
			mode = 0;
		else if (raw_data[1] & 0x02)
			mode = 1;
		else if (raw_data[1] & 0x04)
			mode = 2;

		/* clear mode bits */
		raw_data[1] &= ~0x07;

		if (mode != ssc->mode) {
			hid_dbg(hdev, "entered mode %d\n", mode);
			if (ssc->mode != -1) {
				/* use bit 13 as the mode button */
				raw_data[1] |= 0x04;
			}
			ssc->mode = mode;
		}
	} else if (ssc->quirks & SAITEK_RELEASE_MODE_MMO7 && size == 8) {

		/* M.M.O.7 uses bits 8, 22, 23 for the mode */
		int mode = -1;
		if (raw_data[1] & 0x80)
			mode = 0;
		else if (raw_data[2] & 0x01)
			mode = 1;
		else if (raw_data[2] & 0x02)
			mode = 2;

		/* clear mode bits */
		raw_data[1] &= ~0x80;
		raw_data[2] &= ~0x03;

		if (mode != ssc->mode) {
			hid_dbg(hdev, "entered mode %d\n", mode);
			if (ssc->mode != -1) {
				/* use bit 8 as the mode button, bits 22
				 * and 23 do not represent buttons
				 * according to the HID report descriptor
				 */
				raw_data[1] |= 0x80;
			}
			ssc->mode = mode;
		}
	}

	return 0;
}