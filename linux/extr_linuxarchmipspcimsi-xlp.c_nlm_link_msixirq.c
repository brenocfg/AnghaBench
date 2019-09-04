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
 int XLP_MSIXVEC_PER_LINK ; 

__attribute__((used)) static inline int nlm_link_msixirq(int link, int bit)
{
	return NLM_MSIX_VEC_BASE + link * XLP_MSIXVEC_PER_LINK + bit;
}