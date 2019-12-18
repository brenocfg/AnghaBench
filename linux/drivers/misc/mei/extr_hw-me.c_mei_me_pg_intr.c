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
typedef  int /*<<< orphan*/  u32 ;
struct mei_me_hw {scalar_t__ d0i3_supported; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mei_me_d0i3_intr (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_pg_legacy_intr (struct mei_device*) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 

__attribute__((used)) static void mei_me_pg_intr(struct mei_device *dev, u32 intr_source)
{
	struct mei_me_hw *hw = to_me_hw(dev);

	if (hw->d0i3_supported)
		mei_me_d0i3_intr(dev, intr_source);
	else
		mei_me_pg_legacy_intr(dev);
}