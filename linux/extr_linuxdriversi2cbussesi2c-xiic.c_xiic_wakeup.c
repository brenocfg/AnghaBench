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
struct xiic_i2c {int state; int /*<<< orphan*/  wait; scalar_t__ nmsgs; int /*<<< orphan*/ * rx_msg; int /*<<< orphan*/ * tx_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xiic_wakeup(struct xiic_i2c *i2c, int code)
{
	i2c->tx_msg = NULL;
	i2c->rx_msg = NULL;
	i2c->nmsgs = 0;
	i2c->state = code;
	wake_up(&i2c->wait);
}