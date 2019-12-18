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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct mgsl_struct {int idle_mode; TYPE_1__ params; int /*<<< orphan*/  tcsr_value; scalar_t__ usc_idle_mode; } ;

/* Variables and functions */
#define  HDLC_TXIDLE_ALT_MARK_SPACE 134 
#define  HDLC_TXIDLE_ALT_ZEROS_ONES 133 
#define  HDLC_TXIDLE_FLAGS 132 
#define  HDLC_TXIDLE_MARK 131 
#define  HDLC_TXIDLE_ONES 130 
#define  HDLC_TXIDLE_SPACE 129 
#define  HDLC_TXIDLE_ZEROS 128 
 scalar_t__ IDLEMODE_ALT_MARK_SPACE ; 
 scalar_t__ IDLEMODE_ALT_ONE_ZERO ; 
 scalar_t__ IDLEMODE_FLAGS ; 
 scalar_t__ IDLEMODE_MARK ; 
 int /*<<< orphan*/  IDLEMODE_MASK ; 
 scalar_t__ IDLEMODE_ONE ; 
 scalar_t__ IDLEMODE_SPACE ; 
 scalar_t__ IDLEMODE_ZERO ; 
 scalar_t__ MGSL_MODE_RAW ; 
 int /*<<< orphan*/  TCSR ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_SetTransmitSyncChars (struct mgsl_struct*,unsigned char,unsigned char) ; 

__attribute__((used)) static void usc_set_txidle( struct mgsl_struct *info )
{
	u16 usc_idle_mode = IDLEMODE_FLAGS;

	/* Map API idle mode to USC register bits */

	switch( info->idle_mode ){
	case HDLC_TXIDLE_FLAGS:			usc_idle_mode = IDLEMODE_FLAGS; break;
	case HDLC_TXIDLE_ALT_ZEROS_ONES:	usc_idle_mode = IDLEMODE_ALT_ONE_ZERO; break;
	case HDLC_TXIDLE_ZEROS:			usc_idle_mode = IDLEMODE_ZERO; break;
	case HDLC_TXIDLE_ONES:			usc_idle_mode = IDLEMODE_ONE; break;
	case HDLC_TXIDLE_ALT_MARK_SPACE:	usc_idle_mode = IDLEMODE_ALT_MARK_SPACE; break;
	case HDLC_TXIDLE_SPACE:			usc_idle_mode = IDLEMODE_SPACE; break;
	case HDLC_TXIDLE_MARK:			usc_idle_mode = IDLEMODE_MARK; break;
	}

	info->usc_idle_mode = usc_idle_mode;
	//usc_OutReg(info, TCSR, usc_idle_mode);
	info->tcsr_value &= ~IDLEMODE_MASK;	/* clear idle mode bits */
	info->tcsr_value += usc_idle_mode;
	usc_OutReg(info, TCSR, info->tcsr_value);

	/*
	 * if SyncLink WAN adapter is running in external sync mode, the
	 * transmitter has been set to Monosync in order to try to mimic
	 * a true raw outbound bit stream. Monosync still sends an open/close
	 * sync char at the start/end of a frame. Try to match those sync
	 * patterns to the idle mode set here
	 */
	if ( info->params.mode == MGSL_MODE_RAW ) {
		unsigned char syncpat = 0;
		switch( info->idle_mode ) {
		case HDLC_TXIDLE_FLAGS:
			syncpat = 0x7e;
			break;
		case HDLC_TXIDLE_ALT_ZEROS_ONES:
			syncpat = 0x55;
			break;
		case HDLC_TXIDLE_ZEROS:
		case HDLC_TXIDLE_SPACE:
			syncpat = 0x00;
			break;
		case HDLC_TXIDLE_ONES:
		case HDLC_TXIDLE_MARK:
			syncpat = 0xff;
			break;
		case HDLC_TXIDLE_ALT_MARK_SPACE:
			syncpat = 0xaa;
			break;
		}

		usc_SetTransmitSyncChars(info,syncpat,syncpat);
	}

}