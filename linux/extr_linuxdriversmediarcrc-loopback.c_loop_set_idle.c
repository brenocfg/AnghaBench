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
struct rc_dev {struct loopback_dev* priv; } ;
struct loopback_dev {int idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,char*) ; 

__attribute__((used)) static void loop_set_idle(struct rc_dev *dev, bool enable)
{
	struct loopback_dev *lodev = dev->priv;

	if (lodev->idle != enable) {
		dprintk("%sing idle mode\n", enable ? "enter" : "exit");
		lodev->idle = enable;
	}
}