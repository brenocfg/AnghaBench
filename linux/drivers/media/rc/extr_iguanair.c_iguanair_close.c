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
struct rc_dev {struct iguanair* priv; } ;
struct iguanair {int receiver_on; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int iguanair_receiver (struct iguanair*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iguanair_close(struct rc_dev *rdev)
{
	struct iguanair *ir = rdev->priv;
	int rc;

	mutex_lock(&ir->lock);

	rc = iguanair_receiver(ir, false);
	ir->receiver_on = false;
	if (rc && rc != -ENODEV)
		dev_warn(ir->dev, "failed to disable receiver: %d\n", rc);

	mutex_unlock(&ir->lock);
}