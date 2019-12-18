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
struct gru_tlb_fault_handle {int dummy; } ;
struct gru_control_block_extended {int dummy; } ;

/* Variables and functions */
 unsigned long GRU_CBE_BASE ; 
 unsigned long GRU_TFH_BASE ; 

__attribute__((used)) static inline struct gru_control_block_extended *gru_tfh_to_cbe(
					struct gru_tlb_fault_handle *tfh)
{
	unsigned long cbe;

	cbe = (unsigned long)tfh - GRU_TFH_BASE + GRU_CBE_BASE;
	return (struct gru_control_block_extended*)cbe;
}