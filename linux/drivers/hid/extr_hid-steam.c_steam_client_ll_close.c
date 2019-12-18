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
struct steam_device {int connected; int client_opened; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;
struct hid_device {struct steam_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  lizard_mode ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  steam_input_register (struct steam_device*) ; 
 int /*<<< orphan*/  steam_set_lizard_mode (struct steam_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void steam_client_ll_close(struct hid_device *hdev)
{
	struct steam_device *steam = hdev->driver_data;

	unsigned long flags;
	bool connected;

	spin_lock_irqsave(&steam->lock, flags);
	connected = steam->connected;
	spin_unlock_irqrestore(&steam->lock, flags);

	mutex_lock(&steam->mutex);
	steam->client_opened = false;
	if (connected)
		steam_set_lizard_mode(steam, lizard_mode);
	mutex_unlock(&steam->mutex);

	if (connected)
		steam_input_register(steam);
}