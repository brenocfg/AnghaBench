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
typedef  enum sq_tex_clamp_policy { ____Placeholder_sq_tex_clamp_policy } sq_tex_clamp_policy ;

/* Variables and functions */
 int A2XX_SQ_TEX_1_CLAMP_POLICY__MASK ; 
 int A2XX_SQ_TEX_1_CLAMP_POLICY__SHIFT ; 

__attribute__((used)) static inline uint32_t A2XX_SQ_TEX_1_CLAMP_POLICY(enum sq_tex_clamp_policy val)
{
	return ((val) << A2XX_SQ_TEX_1_CLAMP_POLICY__SHIFT) & A2XX_SQ_TEX_1_CLAMP_POLICY__MASK;
}