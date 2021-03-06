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
typedef  int uint32_t ;
struct TYPE_2__ {int cclk; } ;
struct csio_hw {TYPE_1__ vpd; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
csio_core_ticks_to_us(struct csio_hw *hw, uint32_t ticks)
{
	/* add Core Clock / 2 to round ticks to nearest uS */
	return (ticks * 1000 + hw->vpd.cclk/2) / hw->vpd.cclk;
}