#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uwb_dev_for_each_f ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int device_for_each_child (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

int uwb_dev_for_each(struct uwb_rc *rc, uwb_dev_for_each_f function, void *priv)
{
	return device_for_each_child(&rc->uwb_dev.dev, priv, function);
}