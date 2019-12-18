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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_SDMAENG_ERR_START ; 
 scalar_t__ IS_SDMA_IDLE_START ; 
 scalar_t__ IS_SDMA_PROGRESS_START ; 
 scalar_t__ IS_SDMA_START ; 
 int /*<<< orphan*/  set_intr_bits (struct hfi1_devdata*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void enable_sdma_srcs(struct hfi1_devdata *dd, int i)
{
	set_intr_bits(dd, IS_SDMA_START + i, IS_SDMA_START + i, true);
	set_intr_bits(dd, IS_SDMA_PROGRESS_START + i,
		      IS_SDMA_PROGRESS_START + i, true);
	set_intr_bits(dd, IS_SDMA_IDLE_START + i, IS_SDMA_IDLE_START + i, true);
	set_intr_bits(dd, IS_SDMAENG_ERR_START + i, IS_SDMAENG_ERR_START + i,
		      true);
}