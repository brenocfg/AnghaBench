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
struct bnx2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BNX2_DSP_ADDRESS ; 
 int /*<<< orphan*/  MII_BNX2_DSP_RW_PORT ; 
 int MII_EXPAND_SERDES_CTL ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2_write_phy (struct bnx2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bnx2_5706s_force_link_dn(struct bnx2 *bp, int start)
{
	u32 val;

	bnx2_write_phy(bp, MII_BNX2_DSP_ADDRESS, MII_EXPAND_SERDES_CTL);
	bnx2_read_phy(bp, MII_BNX2_DSP_RW_PORT, &val);
	if (start)
		bnx2_write_phy(bp, MII_BNX2_DSP_RW_PORT, val & 0xff0f);
	else
		bnx2_write_phy(bp, MII_BNX2_DSP_RW_PORT, val | 0xc0);
}