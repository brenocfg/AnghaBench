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
struct acpi_ec {int busy_polling; scalar_t__ polling_guard; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; int /*<<< orphan*/  wait; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ec_event_handler ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct acpi_ec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct acpi_ec *acpi_ec_alloc(void)
{
	struct acpi_ec *ec = kzalloc(sizeof(struct acpi_ec), GFP_KERNEL);

	if (!ec)
		return NULL;
	mutex_init(&ec->mutex);
	init_waitqueue_head(&ec->wait);
	INIT_LIST_HEAD(&ec->list);
	spin_lock_init(&ec->lock);
	INIT_WORK(&ec->work, acpi_ec_event_handler);
	ec->timestamp = jiffies;
	ec->busy_polling = true;
	ec->polling_guard = 0;
	return ec;
}