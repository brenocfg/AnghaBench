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
struct lgdt3306a_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int,int,int) ; 
 int log10_x1000 (int) ; 
 int read_reg (struct lgdt3306a_state*,int) ; 

__attribute__((used)) static u32 lgdt3306a_calculate_snr_x100(struct lgdt3306a_state *state)
{
	u32 mse; /* Mean-Square Error */
	u32 pwr; /* Constelation power */
	u32 snr_x100;

	mse = (read_reg(state, 0x00ec) << 8) |
	      (read_reg(state, 0x00ed));
	pwr = (read_reg(state, 0x00e8) << 8) |
	      (read_reg(state, 0x00e9));

	if (mse == 0) /* no signal */
		return 0;

	snr_x100 = log10_x1000((pwr * 10000) / mse) - 3000;
	dbg_info("mse=%u, pwr=%u, snr_x100=%d\n", mse, pwr, snr_x100);

	return snr_x100;
}