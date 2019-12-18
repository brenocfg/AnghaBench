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
struct wl1271 {int /*<<< orphan*/  dev; TYPE_1__* if_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_block_size ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WL12XX_BUS_BLOCK_SIZE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool wl1271_set_block_size(struct wl1271 *wl)
{
	if (wl->if_ops->set_block_size) {
		wl->if_ops->set_block_size(wl->dev, WL12XX_BUS_BLOCK_SIZE);
		return true;
	}

	return false;
}