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

/* Variables and functions */
 int dma_mode ; 
 int /*<<< orphan*/  use_dma ; 

__attribute__((used)) static char *dma_mode_string(void)
{
	if (!use_dma)
		return "PIO";
	switch (dma_mode) {
	case 0:  return "SLOW DREQ";
	case 1:  return "FAST DREQ";
	case 2:  return "BURST";
	default: return "invalid";
	}
}