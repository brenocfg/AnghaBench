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

/* Variables and functions */
 int ASYNC_EVENT_CODE_GRP_5 ; 
 int ASYNC_EVENT_CODE_MASK ; 
 int ASYNC_EVENT_CODE_SHIFT ; 

__attribute__((used)) static inline bool is_grp5_evt(u32 flags)
{
	return ((flags >> ASYNC_EVENT_CODE_SHIFT) & ASYNC_EVENT_CODE_MASK) ==
			ASYNC_EVENT_CODE_GRP_5;
}