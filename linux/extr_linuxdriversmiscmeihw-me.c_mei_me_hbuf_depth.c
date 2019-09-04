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
struct mei_me_hw {int /*<<< orphan*/  hbuf_depth; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 struct mei_me_hw* to_me_hw (struct mei_device const*) ; 

__attribute__((used)) static u32 mei_me_hbuf_depth(const struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);

	return hw->hbuf_depth;
}