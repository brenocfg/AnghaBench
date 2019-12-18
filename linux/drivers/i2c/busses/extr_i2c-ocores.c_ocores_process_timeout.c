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
struct ocores_i2c {int /*<<< orphan*/  process_lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCI2C_CMD ; 
 int /*<<< orphan*/  OCI2C_CMD_STOP ; 
 int /*<<< orphan*/  STATE_ERROR ; 
 int /*<<< orphan*/  oc_setreg (struct ocores_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ocores_process_timeout(struct ocores_i2c *i2c)
{
	unsigned long flags;

	spin_lock_irqsave(&i2c->process_lock, flags);
	i2c->state = STATE_ERROR;
	oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_STOP);
	spin_unlock_irqrestore(&i2c->process_lock, flags);
}