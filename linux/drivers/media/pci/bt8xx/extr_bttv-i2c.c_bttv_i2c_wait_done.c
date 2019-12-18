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
struct bttv {int i2c_done; int /*<<< orphan*/  i2c_queue; } ;

/* Variables and functions */
 int BT848_INT_RACK ; 
 int EIO ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bttv_i2c_wait_done(struct bttv *btv)
{
	int rc = 0;

	/* timeout */
	if (wait_event_interruptible_timeout(btv->i2c_queue,
	    btv->i2c_done, msecs_to_jiffies(85)) == -ERESTARTSYS)
		rc = -EIO;

	if (btv->i2c_done & BT848_INT_RACK)
		rc = 1;
	btv->i2c_done = 0;
	return rc;
}