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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int DSI_FIFO_GEN_HS_DATA_FULL ; 
 int /*<<< orphan*/  MIPI_GEN_FIFO_STAT_REG (int /*<<< orphan*/ ) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mdfld_wait_for_HS_DATA_FIFO(struct drm_device *dev, u32 pipe)
{
	u32 gen_fifo_stat_reg = MIPI_GEN_FIFO_STAT_REG(pipe);
	int timeout = 0;

	udelay(500);

	/* This will time out after approximately 2+ seconds */
	while ((timeout < 20000) &&
		(REG_READ(gen_fifo_stat_reg) & DSI_FIFO_GEN_HS_DATA_FULL)) {
		udelay(100);
		timeout++;
	}

	if (timeout == 20000)
		DRM_INFO("MIPI: HS Data FIFO was never cleared!\n");
}