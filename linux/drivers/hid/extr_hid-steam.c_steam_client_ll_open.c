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
struct steam_device {int client_opened; int /*<<< orphan*/  mutex; } ;
struct hid_device {struct steam_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  steam_input_unregister (struct steam_device*) ; 

__attribute__((used)) static int steam_client_ll_open(struct hid_device *hdev)
{
	struct steam_device *steam = hdev->driver_data;

	mutex_lock(&steam->mutex);
	steam->client_opened = true;
	mutex_unlock(&steam->mutex);

	steam_input_unregister(steam);

	return 0;
}