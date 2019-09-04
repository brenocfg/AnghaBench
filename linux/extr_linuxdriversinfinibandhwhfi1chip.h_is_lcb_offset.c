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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ LCB_END ; 
 scalar_t__ LCB_START ; 

__attribute__((used)) static inline int is_lcb_offset(u32 offset)
{
	return (offset >= LCB_START && offset < LCB_END);
}