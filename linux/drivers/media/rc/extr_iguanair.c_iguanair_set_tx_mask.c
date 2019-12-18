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
typedef  int uint32_t ;
struct rc_dev {struct iguanair* priv; } ;
struct iguanair {int /*<<< orphan*/  lock; TYPE_1__* packet; } ;
struct TYPE_2__ {int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iguanair_set_tx_mask(struct rc_dev *dev, uint32_t mask)
{
	struct iguanair *ir = dev->priv;

	if (mask > 15)
		return 4;

	mutex_lock(&ir->lock);
	ir->packet->channels = mask << 4;
	mutex_unlock(&ir->lock);

	return 0;
}