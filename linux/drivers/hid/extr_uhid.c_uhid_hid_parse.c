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
struct uhid_device {int /*<<< orphan*/  rd_size; int /*<<< orphan*/  rd_data; } ;
struct hid_device {struct uhid_device* driver_data; } ;

/* Variables and functions */
 int hid_parse_report (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uhid_hid_parse(struct hid_device *hid)
{
	struct uhid_device *uhid = hid->driver_data;

	return hid_parse_report(hid, uhid->rd_data, uhid->rd_size);
}