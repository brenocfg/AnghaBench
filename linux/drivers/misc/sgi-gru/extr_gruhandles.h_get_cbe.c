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
struct gru_control_block_extended {int dummy; } ;

/* Variables and functions */
 int GRU_CBE_BASE ; 
 int GRU_HANDLE_STRIDE ; 

__attribute__((used)) static inline struct gru_control_block_extended *get_cbe(void *base, int ctxnum)
{
	return (struct gru_control_block_extended *)(base + GRU_CBE_BASE +
					ctxnum * GRU_HANDLE_STRIDE);
}