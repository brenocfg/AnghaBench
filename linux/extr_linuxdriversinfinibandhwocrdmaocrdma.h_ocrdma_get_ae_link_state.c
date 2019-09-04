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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int OCRDMA_AE_LSC_LS_MASK ; 
 int OCRDMA_AE_LSC_LS_SHIFT ; 

__attribute__((used)) static inline u8 ocrdma_get_ae_link_state(u32 ae_state)
{
	return ((ae_state & OCRDMA_AE_LSC_LS_MASK) >> OCRDMA_AE_LSC_LS_SHIFT);
}