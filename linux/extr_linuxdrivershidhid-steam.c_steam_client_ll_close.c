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
struct steam_device {int client_opened; scalar_t__ connected; int /*<<< orphan*/  hdev; int /*<<< orphan*/  mutex; } ;
struct hid_device {struct steam_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_hw_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lizard_mode ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  steam_input_register (struct steam_device*) ; 
 int /*<<< orphan*/  steam_set_lizard_mode (struct steam_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void steam_client_ll_close(struct hid_device *hdev)
{
	struct steam_device *steam = hdev->driver_data;

	mutex_lock(&steam->mutex);
	steam->client_opened = false;
	mutex_unlock(&steam->mutex);

	hid_hw_close(steam->hdev);
	if (steam->connected) {
		steam_set_lizard_mode(steam, lizard_mode);
		steam_input_register(steam);
	}
}