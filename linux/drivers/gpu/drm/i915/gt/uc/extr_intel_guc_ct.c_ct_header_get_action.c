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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int GUC_CT_MSG_ACTION_MASK ; 
 unsigned int GUC_CT_MSG_ACTION_SHIFT ; 

__attribute__((used)) static inline unsigned int ct_header_get_action(u32 header)
{
	return (header >> GUC_CT_MSG_ACTION_SHIFT) & GUC_CT_MSG_ACTION_MASK;
}