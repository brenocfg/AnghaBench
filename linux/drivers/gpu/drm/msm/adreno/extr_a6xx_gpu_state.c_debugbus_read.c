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
typedef  int u32 ;
struct msm_gpu {int dummy; } ;

/* Variables and functions */
 int A6XX_DBGC_CFG_DBGBUS_SEL_D_PING_BLK_SEL (int) ; 
 int A6XX_DBGC_CFG_DBGBUS_SEL_D_PING_INDEX (int) ; 
 int /*<<< orphan*/  REG_A6XX_DBGC_CFG_DBGBUS_SEL_A ; 
 int /*<<< orphan*/  REG_A6XX_DBGC_CFG_DBGBUS_SEL_B ; 
 int /*<<< orphan*/  REG_A6XX_DBGC_CFG_DBGBUS_SEL_C ; 
 int /*<<< orphan*/  REG_A6XX_DBGC_CFG_DBGBUS_SEL_D ; 
 int /*<<< orphan*/  REG_A6XX_DBGC_CFG_DBGBUS_TRACE_BUF1 ; 
 int /*<<< orphan*/  REG_A6XX_DBGC_CFG_DBGBUS_TRACE_BUF2 ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int debugbus_read(struct msm_gpu *gpu, u32 block, u32 offset,
		u32 *data)
{
	u32 reg = A6XX_DBGC_CFG_DBGBUS_SEL_D_PING_INDEX(offset) |
		A6XX_DBGC_CFG_DBGBUS_SEL_D_PING_BLK_SEL(block);

	gpu_write(gpu, REG_A6XX_DBGC_CFG_DBGBUS_SEL_A, reg);
	gpu_write(gpu, REG_A6XX_DBGC_CFG_DBGBUS_SEL_B, reg);
	gpu_write(gpu, REG_A6XX_DBGC_CFG_DBGBUS_SEL_C, reg);
	gpu_write(gpu, REG_A6XX_DBGC_CFG_DBGBUS_SEL_D, reg);

	/* Wait 1 us to make sure the data is flowing */
	udelay(1);

	data[0] = gpu_read(gpu, REG_A6XX_DBGC_CFG_DBGBUS_TRACE_BUF2);
	data[1] = gpu_read(gpu, REG_A6XX_DBGC_CFG_DBGBUS_TRACE_BUF1);

	return 2;
}