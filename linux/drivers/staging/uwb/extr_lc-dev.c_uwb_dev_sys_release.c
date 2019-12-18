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
struct uwb_dev {int /*<<< orphan*/  bce; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uwb_dev*) ; 
 int /*<<< orphan*/  memset (struct uwb_dev*,int,int) ; 
 struct uwb_dev* to_uwb_dev (struct device*) ; 
 int /*<<< orphan*/  uwb_bce_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uwb_dev_sys_release(struct device *dev)
{
	struct uwb_dev *uwb_dev = to_uwb_dev(dev);

	uwb_bce_put(uwb_dev->bce);
	memset(uwb_dev, 0x69, sizeof(*uwb_dev));
	kfree(uwb_dev);
}