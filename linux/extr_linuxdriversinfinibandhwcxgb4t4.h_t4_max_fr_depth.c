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

/* Variables and functions */
 int T4_MAX_FR_DSGL_DEPTH ; 
 int T4_MAX_FR_IMMD_DEPTH ; 

__attribute__((used)) static inline int t4_max_fr_depth(int use_dsgl)
{
	return use_dsgl ? T4_MAX_FR_DSGL_DEPTH : T4_MAX_FR_IMMD_DEPTH;
}