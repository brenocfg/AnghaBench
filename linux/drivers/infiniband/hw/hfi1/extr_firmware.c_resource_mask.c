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
typedef  int u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int CR_DYN_SHIFT ; 

__attribute__((used)) static inline u64 resource_mask(u32 hfi1_id, u32 resource)
{
	return ((u64)resource) << (hfi1_id ? CR_DYN_SHIFT : 0);
}