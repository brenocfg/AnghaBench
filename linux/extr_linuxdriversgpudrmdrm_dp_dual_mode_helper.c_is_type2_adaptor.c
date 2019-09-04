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
typedef  int uint8_t ;

/* Variables and functions */
 int DP_DUAL_MODE_REV_TYPE2 ; 
 int DP_DUAL_MODE_TYPE_TYPE2 ; 

__attribute__((used)) static bool is_type2_adaptor(uint8_t adaptor_id)
{
	return adaptor_id == (DP_DUAL_MODE_TYPE_TYPE2 |
			      DP_DUAL_MODE_REV_TYPE2);
}