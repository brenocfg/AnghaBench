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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int sun6i_dsi_ecc_compute (int) ; 

__attribute__((used)) static u32 sun6i_dsi_build_sync_pkt(u8 dt, u8 vc, u8 d0, u8 d1)
{
	u32 val = dt & 0x3f;

	val |= (vc & 3) << 6;
	val |= (d0 & 0xff) << 8;
	val |= (d1 & 0xff) << 16;
	val |= sun6i_dsi_ecc_compute(val) << 24;

	return val;
}