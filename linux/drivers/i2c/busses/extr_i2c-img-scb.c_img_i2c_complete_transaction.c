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
struct img_i2c {int msg_status; int /*<<< orphan*/  msg_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_INACTIVE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_i2c_switch_mode (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_transaction_halt (struct img_i2c*,int) ; 

__attribute__((used)) static void img_i2c_complete_transaction(struct img_i2c *i2c, int status)
{
	img_i2c_switch_mode(i2c, MODE_INACTIVE);
	if (status) {
		i2c->msg_status = status;
		img_i2c_transaction_halt(i2c, false);
	}
	complete(&i2c->msg_complete);
}