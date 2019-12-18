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
struct a6xx_gpu_state_obj {int* data; int /*<<< orphan*/ * handle; } ;
struct a6xx_gpu_state {int dummy; } ;

/* Variables and functions */
 int A6XX_VBIF_CLKON_FORCE_ON_TESTBUS ; 
 int AXI_ARB_BLOCKS ; 
 int /*<<< orphan*/  REG_A6XX_VBIF_CLKON ; 
 int /*<<< orphan*/  REG_A6XX_VBIF_TEST_BUS1_CTRL0 ; 
 int /*<<< orphan*/  REG_A6XX_VBIF_TEST_BUS1_CTRL1 ; 
 int /*<<< orphan*/  REG_A6XX_VBIF_TEST_BUS2_CTRL0 ; 
 int /*<<< orphan*/  REG_A6XX_VBIF_TEST_BUS2_CTRL1 ; 
 int /*<<< orphan*/  REG_A6XX_VBIF_TEST_BUS_OUT_CTRL ; 
 int /*<<< orphan*/  VBIF_DEBUGBUS_BLOCK_SIZE ; 
 int XIN_AXI_BLOCKS ; 
 int XIN_CORE_BLOCKS ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int* state_kcalloc (struct a6xx_gpu_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vbif_debugbus_read (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static void a6xx_get_vbif_debugbus_block(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state,
		struct a6xx_gpu_state_obj *obj)
{
	u32 clk, *ptr;
	int i;

	obj->data = state_kcalloc(a6xx_state, VBIF_DEBUGBUS_BLOCK_SIZE,
		sizeof(u32));
	if (!obj->data)
		return;

	obj->handle = NULL;

	/* Get the current clock setting */
	clk = gpu_read(gpu, REG_A6XX_VBIF_CLKON);

	/* Force on the bus so we can read it */
	gpu_write(gpu, REG_A6XX_VBIF_CLKON,
		clk | A6XX_VBIF_CLKON_FORCE_ON_TESTBUS);

	/* We will read from BUS2 first, so disable BUS1 */
	gpu_write(gpu, REG_A6XX_VBIF_TEST_BUS1_CTRL0, 0);

	/* Enable the VBIF bus for reading */
	gpu_write(gpu, REG_A6XX_VBIF_TEST_BUS_OUT_CTRL, 1);

	ptr = obj->data;

	for (i = 0; i < AXI_ARB_BLOCKS; i++)
		ptr += vbif_debugbus_read(gpu,
			REG_A6XX_VBIF_TEST_BUS2_CTRL0,
			REG_A6XX_VBIF_TEST_BUS2_CTRL1,
			1 << (i + 16), 16, ptr);

	for (i = 0; i < XIN_AXI_BLOCKS; i++)
		ptr += vbif_debugbus_read(gpu,
			REG_A6XX_VBIF_TEST_BUS2_CTRL0,
			REG_A6XX_VBIF_TEST_BUS2_CTRL1,
			1 << i, 18, ptr);

	/* Stop BUS2 so we can turn on BUS1 */
	gpu_write(gpu, REG_A6XX_VBIF_TEST_BUS2_CTRL0, 0);

	for (i = 0; i < XIN_CORE_BLOCKS; i++)
		ptr += vbif_debugbus_read(gpu,
			REG_A6XX_VBIF_TEST_BUS1_CTRL0,
			REG_A6XX_VBIF_TEST_BUS1_CTRL1,
			1 << i, 12, ptr);

	/* Restore the VBIF clock setting */
	gpu_write(gpu, REG_A6XX_VBIF_CLKON, clk);
}