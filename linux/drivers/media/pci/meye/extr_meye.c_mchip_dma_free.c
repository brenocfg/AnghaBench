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
struct TYPE_2__ {scalar_t__ mchip_dmahandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  mchip_dma_setup (int /*<<< orphan*/ ) ; 
 TYPE_1__ meye ; 
 int /*<<< orphan*/  ptable_free () ; 

__attribute__((used)) static void mchip_dma_free(void)
{
	if (meye.mchip_dmahandle) {
		mchip_dma_setup(0);
		ptable_free();
	}
}