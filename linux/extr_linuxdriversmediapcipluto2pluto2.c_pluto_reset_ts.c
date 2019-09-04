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
struct pluto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TSCR ; 
 int TSCR_RSTN ; 
 int pluto_readreg (struct pluto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_write_tscr (struct pluto*,int) ; 

__attribute__((used)) static void pluto_reset_ts(struct pluto *pluto, int reenable)
{
	u32 val = pluto_readreg(pluto, REG_TSCR);

	if (val & TSCR_RSTN) {
		val &= ~TSCR_RSTN;
		pluto_write_tscr(pluto, val);
	}
	if (reenable) {
		val |= TSCR_RSTN;
		pluto_write_tscr(pluto, val);
	}
}