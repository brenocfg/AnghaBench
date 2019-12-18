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
struct gru_tlb_global_handle {int dummy; } ;

/* Variables and functions */
 int GRU_HANDLE_STRIDE ; 
 int GRU_TGH_BASE ; 

__attribute__((used)) static inline struct gru_tlb_global_handle *get_tgh(void *base, int ctxnum)
{
	return (struct gru_tlb_global_handle *)(base + GRU_TGH_BASE +
					ctxnum * GRU_HANDLE_STRIDE);
}