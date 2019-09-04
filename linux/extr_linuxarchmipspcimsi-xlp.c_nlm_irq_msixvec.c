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
 int NLM_MSIX_VEC_BASE ; 
 int XLP_MSIXVEC_TOTAL ; 

__attribute__((used)) static inline int nlm_irq_msixvec(int irq)
{
	return (irq - NLM_MSIX_VEC_BASE) % XLP_MSIXVEC_TOTAL;
}