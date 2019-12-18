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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int SUN6I_DSI_BLK_PD (int /*<<< orphan*/ ) ; 
 int SUN6I_DSI_BLK_PF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun6i_dsi_crc_repeat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u32 sun6i_dsi_build_blk1_pkt(u16 pd, u8 *buffer, size_t len)
{
	u32 val = SUN6I_DSI_BLK_PD(pd);

	return val | SUN6I_DSI_BLK_PF(sun6i_dsi_crc_repeat(pd, buffer, len));
}