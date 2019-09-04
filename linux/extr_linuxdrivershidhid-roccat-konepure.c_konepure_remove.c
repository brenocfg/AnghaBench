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
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  konepure_remove_specials (struct hid_device*) ; 

__attribute__((used)) static void konepure_remove(struct hid_device *hdev)
{
	konepure_remove_specials(hdev);
	hid_hw_stop(hdev);
}