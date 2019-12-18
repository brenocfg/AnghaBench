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
 scalar_t__ is_field_set (int,int) ; 

__attribute__((used)) static inline bool unsupported(u32 conf, u32 conf_mask, u32 val, u32 mask)
{
	return !(conf & conf_mask) && is_field_set(val, mask);
}