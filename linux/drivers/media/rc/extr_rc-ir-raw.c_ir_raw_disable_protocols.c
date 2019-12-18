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
typedef  int /*<<< orphan*/  u64 ;
struct rc_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  enabled_protocols; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ir_raw_disable_protocols(struct rc_dev *dev, u64 protocols)
{
	mutex_lock(&dev->lock);
	dev->enabled_protocols &= ~protocols;
	mutex_unlock(&dev->lock);
}