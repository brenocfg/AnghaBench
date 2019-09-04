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
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_hiddev_list ; 
 int /*<<< orphan*/  hid_match_id (struct hid_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hid_hiddev(struct hid_device *hdev)
{
	return !!hid_match_id(hdev, hid_hiddev_list);
}