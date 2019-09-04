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
struct dib3000mc_state {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
#define  QAM_16 130 
#define  QAM_64 129 
#define  QPSK 128 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 

__attribute__((used)) static void dib3000mc_set_adp_cfg(struct dib3000mc_state *state, s16 qam)
{
	u16 cfg[4] = { 0 },reg;
	switch (qam) {
		case QPSK:
			cfg[0] = 0x099a; cfg[1] = 0x7fae; cfg[2] = 0x0333; cfg[3] = 0x7ff0;
			break;
		case QAM_16:
			cfg[0] = 0x023d; cfg[1] = 0x7fdf; cfg[2] = 0x00a4; cfg[3] = 0x7ff0;
			break;
		case QAM_64:
			cfg[0] = 0x0148; cfg[1] = 0x7ff0; cfg[2] = 0x00a4; cfg[3] = 0x7ff8;
			break;
	}
	for (reg = 129; reg < 133; reg++)
		dib3000mc_write_word(state, reg, cfg[reg - 129]);
}