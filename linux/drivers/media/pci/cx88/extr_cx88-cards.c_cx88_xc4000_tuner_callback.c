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
struct cx88_core {int boardnr; } ;

/* Variables and functions */
#define  CX88_BOARD_WINFAST_DTV1800H_XC4000 131 
#define  CX88_BOARD_WINFAST_DTV2000H_PLUS 130 
#define  CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36 129 
#define  CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43 128 
 int EINVAL ; 
 int cx88_xc4000_winfast2000h_plus_callback (struct cx88_core*,int,int) ; 

__attribute__((used)) static int cx88_xc4000_tuner_callback(struct cx88_core *core,
				      int command, int arg)
{
	/* Board-specific callbacks */
	switch (core->boardnr) {
	case CX88_BOARD_WINFAST_DTV1800H_XC4000:
	case CX88_BOARD_WINFAST_DTV2000H_PLUS:
	case CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36:
	case CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43:
		return cx88_xc4000_winfast2000h_plus_callback(core,
							      command, arg);
	}
	return -EINVAL;
}