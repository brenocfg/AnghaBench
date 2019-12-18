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
struct bnx2x_func_sp_drv_ops {int /*<<< orphan*/  (* reset_hw_port ) (struct bnx2x*) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_func_reset_func (struct bnx2x*,struct bnx2x_func_sp_drv_ops const*) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*) ; 

__attribute__((used)) static inline void bnx2x_func_reset_port(struct bnx2x *bp,
					const struct bnx2x_func_sp_drv_ops *drv)
{
	drv->reset_hw_port(bp);
	bnx2x_func_reset_func(bp, drv);
}