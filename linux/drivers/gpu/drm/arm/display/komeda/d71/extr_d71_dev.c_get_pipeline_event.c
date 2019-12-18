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
typedef  int u64 ;
typedef  int u32 ;
struct d71_pipeline {int dummy; } ;

/* Variables and functions */
 int GLB_IRQ_STATUS_CU0 ; 
 int GLB_IRQ_STATUS_CU1 ; 
 int GLB_IRQ_STATUS_DOU0 ; 
 int GLB_IRQ_STATUS_DOU1 ; 
 int GLB_IRQ_STATUS_LPU0 ; 
 int GLB_IRQ_STATUS_LPU1 ; 
 int get_cu_event (struct d71_pipeline*) ; 
 int get_dou_event (struct d71_pipeline*) ; 
 int get_lpu_event (struct d71_pipeline*) ; 

__attribute__((used)) static u64 get_pipeline_event(struct d71_pipeline *d71_pipeline, u32 gcu_status)
{
	u32 evts = 0ULL;

	if (gcu_status & (GLB_IRQ_STATUS_LPU0 | GLB_IRQ_STATUS_LPU1))
		evts |= get_lpu_event(d71_pipeline);

	if (gcu_status & (GLB_IRQ_STATUS_CU0 | GLB_IRQ_STATUS_CU1))
		evts |= get_cu_event(d71_pipeline);

	if (gcu_status & (GLB_IRQ_STATUS_DOU0 | GLB_IRQ_STATUS_DOU1))
		evts |= get_dou_event(d71_pipeline);

	return evts;
}