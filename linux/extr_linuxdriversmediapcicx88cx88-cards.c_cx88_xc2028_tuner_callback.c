#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cx88_core {int boardnr; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_NANO 139 
#define  CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO 138 
#define  CX88_BOARD_GENIATECH_X8000_MT 137 
#define  CX88_BOARD_KWORLD_ATSC_120 136 
#define  CX88_BOARD_POWERCOLOR_REAL_ANGEL 135 
#define  CX88_BOARD_PROLINK_PV_8000GT 134 
#define  CX88_BOARD_PROLINK_PV_GLOBAL_XTREME 133 
#define  CX88_BOARD_WINFAST_DTV1800H 132 
#define  CX88_BOARD_WINFAST_TV2000_XP_GLOBAL 131 
#define  CX88_RADIO 130 
#define  CX88_VMUX_DVB 129 
 int EINVAL ; 
 TYPE_1__ INPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  MO_GP1_IO ; 
 int /*<<< orphan*/  MO_GP2_IO ; 
#define  XC2028_TUNER_RESET 128 
 int cx88_dvico_xc2028_callback (struct cx88_core*,int,int) ; 
 int cx88_pv_8000gt_callback (struct cx88_core*,int,int) ; 
 int cx88_xc3028_geniatech_tuner_callback (struct cx88_core*,int,int) ; 
 int cx88_xc3028_winfast1800h_callback (struct cx88_core*,int,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int cx88_xc2028_tuner_callback(struct cx88_core *core,
				      int command, int arg)
{
	/* Board-specific callbacks */
	switch (core->boardnr) {
	case CX88_BOARD_POWERCOLOR_REAL_ANGEL:
	case CX88_BOARD_GENIATECH_X8000_MT:
	case CX88_BOARD_KWORLD_ATSC_120:
		return cx88_xc3028_geniatech_tuner_callback(core,
							command, arg);
	case CX88_BOARD_PROLINK_PV_8000GT:
	case CX88_BOARD_PROLINK_PV_GLOBAL_XTREME:
		return cx88_pv_8000gt_callback(core, command, arg);
	case CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO:
	case CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_NANO:
		return cx88_dvico_xc2028_callback(core, command, arg);
	case CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
	case CX88_BOARD_WINFAST_DTV1800H:
		return cx88_xc3028_winfast1800h_callback(core, command, arg);
	}

	switch (command) {
	case XC2028_TUNER_RESET:
		switch (INPUT(core->input).type) {
		case CX88_RADIO:
			dprintk(1, "setting GPIO to radio!\n");
			cx_write(MO_GP0_IO, 0x4ff);
			mdelay(250);
			cx_write(MO_GP2_IO, 0xff);
			mdelay(250);
			break;
		case CX88_VMUX_DVB:	/* Digital TV*/
		default:		/* Analog TV */
			dprintk(1, "setting GPIO to TV!\n");
			break;
		}
		cx_write(MO_GP1_IO, 0x101010);
		mdelay(250);
		cx_write(MO_GP1_IO, 0x101000);
		mdelay(250);
		cx_write(MO_GP1_IO, 0x101010);
		mdelay(250);
		return 0;
	}
	return -EINVAL;
}