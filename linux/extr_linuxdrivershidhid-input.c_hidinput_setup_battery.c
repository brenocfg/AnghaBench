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
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int hidinput_setup_battery(struct hid_device *dev, unsigned report_type,
				  struct hid_field *field)
{
	return 0;
}