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
typedef  enum debug_print_features { ____Placeholder_debug_print_features } debug_print_features ;

/* Variables and functions */
 int REGDUMP_HEADER_ENGINE_SHIFT ; 
 int REGDUMP_HEADER_FEATURE_SHIFT ; 
 int REGDUMP_HEADER_OMIT_ENGINE_SHIFT ; 

__attribute__((used)) static u32 qed_calc_regdump_header(enum debug_print_features feature,
				   int engine, u32 feature_size, u8 omit_engine)
{
	/* Insert the engine, feature and mode inside the header and combine it
	 * with feature size.
	 */
	return feature_size | (feature << REGDUMP_HEADER_FEATURE_SHIFT) |
	       (omit_engine << REGDUMP_HEADER_OMIT_ENGINE_SHIFT) |
	       (engine << REGDUMP_HEADER_ENGINE_SHIFT);
}