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
struct uhid_device {int dummy; } ;
struct hid_device {scalar_t__ claimed; struct uhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  UHID_STOP ; 
 int /*<<< orphan*/  uhid_queue_event (struct uhid_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uhid_hid_stop(struct hid_device *hid)
{
	struct uhid_device *uhid = hid->driver_data;

	hid->claimed = 0;
	uhid_queue_event(uhid, UHID_STOP);
}