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
typedef  enum a3xx_rb_blend_opcode { ____Placeholder_a3xx_rb_blend_opcode } a3xx_rb_blend_opcode ;

/* Variables and functions */
 int A4XX_RB_MRT_BLEND_CONTROL_ALPHA_BLEND_OPCODE__MASK ; 
 int A4XX_RB_MRT_BLEND_CONTROL_ALPHA_BLEND_OPCODE__SHIFT ; 

__attribute__((used)) static inline uint32_t A4XX_RB_MRT_BLEND_CONTROL_ALPHA_BLEND_OPCODE(enum a3xx_rb_blend_opcode val)
{
	return ((val) << A4XX_RB_MRT_BLEND_CONTROL_ALPHA_BLEND_OPCODE__SHIFT) & A4XX_RB_MRT_BLEND_CONTROL_ALPHA_BLEND_OPCODE__MASK;
}