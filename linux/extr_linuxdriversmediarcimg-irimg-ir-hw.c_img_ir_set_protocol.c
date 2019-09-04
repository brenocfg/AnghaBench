#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct rc_dev {int /*<<< orphan*/  lock; void* allowed_wakeup_protocols; void* enabled_protocols; } ;
struct TYPE_2__ {struct rc_dev* rdev; } ;
struct img_ir_priv {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_ir_set_protocol(struct img_ir_priv *priv, u64 proto)
{
	struct rc_dev *rdev = priv->hw.rdev;

	mutex_lock(&rdev->lock);
	rdev->enabled_protocols = proto;
	rdev->allowed_wakeup_protocols = proto;
	mutex_unlock(&rdev->lock);
}