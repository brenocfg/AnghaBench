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
typedef  enum xsdfec_axis_word_include { ____Placeholder_xsdfec_axis_word_include } xsdfec_axis_word_include ;

/* Variables and functions */
 int XSDFEC_FIXED_VALUE ; 
 int XSDFEC_IN_BLOCK ; 
 int XSDFEC_PER_AXI_TRANSACTION ; 

__attribute__((used)) static u32 xsdfec_translate_axis_words_cfg_val(enum xsdfec_axis_word_include
	axis_word_inc_cfg)
{
	u32 axis_words_field = 0;

	if (axis_word_inc_cfg == XSDFEC_FIXED_VALUE ||
	    axis_word_inc_cfg == XSDFEC_IN_BLOCK)
		axis_words_field = 0;
	else if (axis_word_inc_cfg == XSDFEC_PER_AXI_TRANSACTION)
		axis_words_field = 1;

	return axis_words_field;
}