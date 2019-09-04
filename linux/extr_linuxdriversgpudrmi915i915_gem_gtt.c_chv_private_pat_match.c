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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ CHV_PPAT_GET_SNOOP (int /*<<< orphan*/ ) ; 
 unsigned int INTEL_PPAT_PERFECT_MATCH ; 

__attribute__((used)) static unsigned int chv_private_pat_match(u8 src, u8 dst)
{
	return (CHV_PPAT_GET_SNOOP(src) == CHV_PPAT_GET_SNOOP(dst)) ?
		INTEL_PPAT_PERFECT_MATCH : 0;
}