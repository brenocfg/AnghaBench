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
typedef  int u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 unsigned int NCCTRL_WIN ; 
 unsigned int NMTUS ; 
 unsigned int ROWINDEX_V (int) ; 
 int /*<<< orphan*/  TP_CCTRL_TABLE_A ; 
 scalar_t__ t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

void t4_read_cong_tbl(struct adapter *adap, u16 incr[NMTUS][NCCTRL_WIN])
{
	unsigned int mtu, w;

	for (mtu = 0; mtu < NMTUS; ++mtu)
		for (w = 0; w < NCCTRL_WIN; ++w) {
			t4_write_reg(adap, TP_CCTRL_TABLE_A,
				     ROWINDEX_V(0xffff) | (mtu << 5) | w);
			incr[mtu][w] = (u16)t4_read_reg(adap,
						TP_CCTRL_TABLE_A) & 0x1fff;
		}
}