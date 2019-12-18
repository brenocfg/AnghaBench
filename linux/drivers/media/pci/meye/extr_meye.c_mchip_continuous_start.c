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
struct TYPE_2__ {int /*<<< orphan*/  mchip_mode; int /*<<< orphan*/  mchip_dmahandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_HIC_CMD ; 
 int /*<<< orphan*/  MCHIP_HIC_CMD_START ; 
 int /*<<< orphan*/  MCHIP_HIC_MODE ; 
 int /*<<< orphan*/  MCHIP_HIC_MODE_CONT_OUT ; 
 int /*<<< orphan*/  mchip_delay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_dma_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_hic_stop () ; 
 int /*<<< orphan*/  mchip_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_set_framerate () ; 
 int /*<<< orphan*/  mchip_subsample () ; 
 TYPE_1__ meye ; 

__attribute__((used)) static void mchip_continuous_start(void)
{
	mchip_hic_stop();
	mchip_subsample();
	mchip_set_framerate();
	mchip_dma_setup(meye.mchip_dmahandle);

	meye.mchip_mode = MCHIP_HIC_MODE_CONT_OUT;

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_CONT_OUT);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);
}