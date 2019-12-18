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
struct mei_me_hw {scalar_t__ d0i3_supported; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int mei_me_d0i3_enter_sync (struct mei_device*) ; 
 int mei_me_pg_legacy_enter_sync (struct mei_device*) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 

int mei_me_pg_enter_sync(struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);

	if (hw->d0i3_supported)
		return mei_me_d0i3_enter_sync(dev);
	else
		return mei_me_pg_legacy_enter_sync(dev);
}