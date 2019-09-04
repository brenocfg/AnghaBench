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
struct brcmnand_controller {int flash_dma_base; } ;

/* Variables and functions */

__attribute__((used)) static inline bool has_flash_dma(struct brcmnand_controller *ctrl)
{
	return ctrl->flash_dma_base;
}