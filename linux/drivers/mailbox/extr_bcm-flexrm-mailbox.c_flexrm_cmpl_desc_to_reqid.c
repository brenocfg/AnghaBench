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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int CMPL_OPAQUE_MASK ; 

__attribute__((used)) static u32 flexrm_cmpl_desc_to_reqid(u64 cmpl_desc)
{
	return (u32)(cmpl_desc & CMPL_OPAQUE_MASK);
}