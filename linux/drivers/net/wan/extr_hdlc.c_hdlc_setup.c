#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int carrier; int /*<<< orphan*/  state_lock; scalar_t__ open; } ;
typedef  TYPE_1__ hdlc_device ;

/* Variables and functions */
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_setup_dev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdlc_setup(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);

	hdlc_setup_dev(dev);
	hdlc->carrier = 1;
	hdlc->open = 0;
	spin_lock_init(&hdlc->state_lock);
}