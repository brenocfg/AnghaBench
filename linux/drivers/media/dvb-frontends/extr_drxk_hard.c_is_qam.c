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
struct drxk_state {scalar_t__ m_operation_mode; } ;

/* Variables and functions */
 scalar_t__ OM_QAM_ITU_A ; 
 scalar_t__ OM_QAM_ITU_B ; 
 scalar_t__ OM_QAM_ITU_C ; 

__attribute__((used)) static bool is_qam(struct drxk_state *state)
{
	return state->m_operation_mode == OM_QAM_ITU_A ||
	    state->m_operation_mode == OM_QAM_ITU_B ||
	    state->m_operation_mode == OM_QAM_ITU_C;
}