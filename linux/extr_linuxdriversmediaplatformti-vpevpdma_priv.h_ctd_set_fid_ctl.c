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
 int CTD_FID1_SHFT ; 
 int CTD_FID2_SHFT ; 

__attribute__((used)) static inline u32 ctd_set_fid_ctl(int fid0, int fid1, int fid2)
{
	return (fid2 << CTD_FID2_SHFT) | (fid1 << CTD_FID1_SHFT) | fid0;
}