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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DSI_BLANKING_PACKET ; 
 int /*<<< orphan*/  sun6i_dsi_build_sync_pkt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u32 sun6i_dsi_build_blk0_pkt(u8 vc, u16 wc)
{
	return sun6i_dsi_build_sync_pkt(MIPI_DSI_BLANKING_PACKET, vc,
					wc & 0xff, wc >> 8);
}