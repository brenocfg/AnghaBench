#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* mode; int /*<<< orphan*/  size; int /*<<< orphan*/  start; scalar_t__ p; } ;
struct TYPE_3__ {void* mode; int /*<<< orphan*/  size; int /*<<< orphan*/  start; scalar_t__ p; } ;
struct inf_hw {TYPE_2__ addr; TYPE_1__ cfg; } ;

/* Variables and functions */
 void* AM_NONE ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
release_io(struct inf_hw *hw)
{
	if (hw->cfg.mode) {
		if (hw->cfg.p) {
			release_mem_region(hw->cfg.start, hw->cfg.size);
			iounmap(hw->cfg.p);
		} else
			release_region(hw->cfg.start, hw->cfg.size);
		hw->cfg.mode = AM_NONE;
	}
	if (hw->addr.mode) {
		if (hw->addr.p) {
			release_mem_region(hw->addr.start, hw->addr.size);
			iounmap(hw->addr.p);
		} else
			release_region(hw->addr.start, hw->addr.size);
		hw->addr.mode = AM_NONE;
	}
}