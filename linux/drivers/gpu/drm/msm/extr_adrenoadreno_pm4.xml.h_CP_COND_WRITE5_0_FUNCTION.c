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
typedef  enum cp_cond_function { ____Placeholder_cp_cond_function } cp_cond_function ;

/* Variables and functions */
 int CP_COND_WRITE5_0_FUNCTION__MASK ; 
 int CP_COND_WRITE5_0_FUNCTION__SHIFT ; 

__attribute__((used)) static inline uint32_t CP_COND_WRITE5_0_FUNCTION(enum cp_cond_function val)
{
	return ((val) << CP_COND_WRITE5_0_FUNCTION__SHIFT) & CP_COND_WRITE5_0_FUNCTION__MASK;
}