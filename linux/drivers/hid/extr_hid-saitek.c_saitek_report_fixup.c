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
struct saitek_sc {int quirks; } ;
struct hid_device {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int SAITEK_FIX_PS1000 ; 
 struct saitek_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 

__attribute__((used)) static __u8 *saitek_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	struct saitek_sc *ssc = hid_get_drvdata(hdev);

	if ((ssc->quirks & SAITEK_FIX_PS1000) && *rsize == 137 &&
			rdesc[20] == 0x09 && rdesc[21] == 0x33 &&
			rdesc[94] == 0x81 && rdesc[95] == 0x03 &&
			rdesc[110] == 0x81 && rdesc[111] == 0x03) {

		hid_info(hdev, "Fixing up Saitek PS1000 report descriptor\n");

		/* convert spurious axis to a "noop" Logical Minimum (0) */
		rdesc[20] = 0x15;
		rdesc[21] = 0x00;

		/* clear constant bit on buttons and d-pad */
		rdesc[95] = 0x02;
		rdesc[111] = 0x02;

	}
	return rdesc;
}