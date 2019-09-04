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
struct xiic_i2c {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xiic_start_xfer (struct xiic_i2c*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xiic_reinit (struct xiic_i2c*) ; 

__attribute__((used)) static void xiic_start_xfer(struct xiic_i2c *i2c)
{
	mutex_lock(&i2c->lock);
	xiic_reinit(i2c);
	__xiic_start_xfer(i2c);
	mutex_unlock(&i2c->lock);
}