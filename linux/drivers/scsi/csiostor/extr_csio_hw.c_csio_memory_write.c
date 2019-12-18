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
typedef  int /*<<< orphan*/  u32 ;
struct csio_hw {TYPE_1__* chip_ops; } ;
struct TYPE_2__ {int (* chip_memory_rw ) (struct csio_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MEMWIN_CSIOSTOR ; 
 int stub1 (struct csio_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csio_memory_write(struct csio_hw *hw, int mtype, u32 addr, u32 len, u32 *buf)
{
	return hw->chip_ops->chip_memory_rw(hw, MEMWIN_CSIOSTOR, mtype,
					    addr, len, buf, 0);
}