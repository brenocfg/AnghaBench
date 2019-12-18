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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_PF_SLC_VIRTUAL_WINDOW ; 
 int /*<<< orphan*/  __genwqe_readq (struct genwqe_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __genwqe_writeq (struct genwqe_dev*,int /*<<< orphan*/ ,int) ; 

u64 genwqe_read_vreg(struct genwqe_dev *cd, u32 reg, int func)
{
	__genwqe_writeq(cd, IO_PF_SLC_VIRTUAL_WINDOW, func & 0xf);
	return __genwqe_readq(cd, reg);
}