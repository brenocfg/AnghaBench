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
struct hid_device_id {scalar_t__ bus; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ hid_match_one_id (struct hid_device const*,struct hid_device_id const*) ; 

const struct hid_device_id *hid_match_id(const struct hid_device *hdev,
		const struct hid_device_id *id)
{
	for (; id->bus; id++)
		if (hid_match_one_id(hdev, id))
			return id;

	return NULL;
}