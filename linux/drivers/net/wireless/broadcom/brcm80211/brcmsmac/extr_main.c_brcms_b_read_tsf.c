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
struct brcms_hardware {struct bcma_device* d11core; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsf_timerhigh ; 
 int /*<<< orphan*/  tsf_timerlow ; 

__attribute__((used)) static void
brcms_b_read_tsf(struct brcms_hardware *wlc_hw, u32 *tsf_l_ptr,
		  u32 *tsf_h_ptr)
{
	struct bcma_device *core = wlc_hw->d11core;

	/* read the tsf timer low, then high to get an atomic read */
	*tsf_l_ptr = bcma_read32(core, D11REGOFFS(tsf_timerlow));
	*tsf_h_ptr = bcma_read32(core, D11REGOFFS(tsf_timerhigh));
}