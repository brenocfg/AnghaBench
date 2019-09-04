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
struct steam_device {int /*<<< orphan*/  hdev; } ;
struct hid_device {struct steam_device* driver_data; } ;

/* Variables and functions */
 int hid_hw_raw_request (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ *,size_t,unsigned char,int) ; 

__attribute__((used)) static int steam_client_ll_raw_request(struct hid_device *hdev,
				unsigned char reportnum, u8 *buf,
				size_t count, unsigned char report_type,
				int reqtype)
{
	struct steam_device *steam = hdev->driver_data;

	return hid_hw_raw_request(steam->hdev, reportnum, buf, count,
			report_type, reqtype);
}