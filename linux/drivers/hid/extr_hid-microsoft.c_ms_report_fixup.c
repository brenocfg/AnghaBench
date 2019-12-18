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
struct ms_data {unsigned long quirks; } ;
struct hid_device {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 unsigned long MS_RDESC ; 
 struct ms_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 

__attribute__((used)) static __u8 *ms_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	struct ms_data *ms = hid_get_drvdata(hdev);
	unsigned long quirks = ms->quirks;

	/*
	 * Microsoft Wireless Desktop Receiver (Model 1028) has
	 * 'Usage Min/Max' where it ought to have 'Physical Min/Max'
	 */
	if ((quirks & MS_RDESC) && *rsize == 571 && rdesc[557] == 0x19 &&
			rdesc[559] == 0x29) {
		hid_info(hdev, "fixing up Microsoft Wireless Receiver Model 1028 report descriptor\n");
		rdesc[557] = 0x35;
		rdesc[559] = 0x45;
	}
	return rdesc;
}