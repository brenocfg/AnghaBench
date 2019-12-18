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
struct gb_hid {int /*<<< orphan*/  hdesc; int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_HID_TYPE_GET_DESC ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gb_hid_get_desc(struct gb_hid *ghid)
{
	return gb_operation_sync(ghid->connection, GB_HID_TYPE_GET_DESC, NULL,
				 0, &ghid->hdesc, sizeof(ghid->hdesc));
}