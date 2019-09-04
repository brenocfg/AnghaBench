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
typedef  int uint32_t ;

/* Variables and functions */
 int __offset_OVLP (int) ; 

__attribute__((used)) static inline uint32_t REG_MDP4_OVLP_CSC_POST_BV(uint32_t i0, uint32_t i1) { return 0x00002580 + __offset_OVLP(i0) + 0x4*i1; }