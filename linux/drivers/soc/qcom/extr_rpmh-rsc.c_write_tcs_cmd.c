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
struct rsc_drv {scalar_t__ tcs_base; } ;

/* Variables and functions */
 int RSC_DRV_CMD_OFFSET ; 
 int RSC_DRV_TCS_OFFSET ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void write_tcs_cmd(struct rsc_drv *drv, int reg, int tcs_id, int cmd_id,
			  u32 data)
{
	writel_relaxed(data, drv->tcs_base + reg + RSC_DRV_TCS_OFFSET * tcs_id +
		       RSC_DRV_CMD_OFFSET * cmd_id);
}