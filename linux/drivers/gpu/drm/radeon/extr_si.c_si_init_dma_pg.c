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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PGFSM_CONFIG ; 
 int /*<<< orphan*/  DMA_PGFSM_WRITE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_init_dma_pg(struct radeon_device *rdev)
{
	u32 tmp;

	WREG32(DMA_PGFSM_WRITE,  0x00002000);
	WREG32(DMA_PGFSM_CONFIG, 0x100010ff);

	for (tmp = 0; tmp < 5; tmp++)
		WREG32(DMA_PGFSM_WRITE, 0);
}