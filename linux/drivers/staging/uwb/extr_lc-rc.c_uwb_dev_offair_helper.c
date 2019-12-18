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
struct uwb_dev {int /*<<< orphan*/  rc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int __uwb_dev_offair (struct uwb_dev*,int /*<<< orphan*/ ) ; 
 struct uwb_dev* to_uwb_dev (struct device*) ; 

__attribute__((used)) static int uwb_dev_offair_helper(struct device *dev, void *priv)
{
	struct uwb_dev *uwb_dev = to_uwb_dev(dev);

	return __uwb_dev_offair(uwb_dev, uwb_dev->rc);
}