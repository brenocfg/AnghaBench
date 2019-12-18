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
typedef  size_t uint ;
struct brcms_hardware {int /*<<< orphan*/ ** di; } ;

/* Variables and functions */
 size_t NFIFO ; 
 int /*<<< orphan*/  dma_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcms_b_detach_dmapio(struct brcms_hardware *wlc_hw)
{
	uint j;

	for (j = 0; j < NFIFO; j++) {
		if (wlc_hw->di[j]) {
			dma_detach(wlc_hw->di[j]);
			wlc_hw->di[j] = NULL;
		}
	}
}