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
typedef  int u32 ;
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int MI_SEMAPHORE_COMPARE ; 
 int MI_SEMAPHORE_MBOX ; 
 int MI_SEMAPHORE_REGISTER ; 
 int MI_SEMAPHORE_SYNC_MASK ; 

__attribute__((used)) static bool
ipehr_is_semaphore_wait(struct intel_engine_cs *engine, u32 ipehr)
{
	ipehr &= ~MI_SEMAPHORE_SYNC_MASK;
	return ipehr == (MI_SEMAPHORE_MBOX | MI_SEMAPHORE_COMPARE |
			 MI_SEMAPHORE_REGISTER);
}