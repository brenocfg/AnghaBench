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
struct loopback_dev {int learning; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,char*) ; 

__attribute__((used)) static int loop_set_learning_mode(struct rc_dev *dev, int enable)
{
	struct loopback_dev *lodev = dev->priv;

	if (lodev->learning != enable) {
		dprintk("%sing learning mode\n", enable ? "enter" : "exit");
		lodev->learning = !!enable;
	}

	return 0;
}