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
struct tap_queue {int /*<<< orphan*/  tap; } ;
struct tap_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 struct tap_dev* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tap_dev *tap_get_tap_dev(struct tap_queue *q)
{
	struct tap_dev *tap;

	ASSERT_RTNL();
	tap = rtnl_dereference(q->tap);
	if (tap)
		dev_hold(tap->dev);

	return tap;
}