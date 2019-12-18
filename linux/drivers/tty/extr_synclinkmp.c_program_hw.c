#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__* tty; } ;
struct TYPE_15__ {scalar_t__ mode; } ;
struct TYPE_19__ {int ie1_value; int /*<<< orphan*/  lock; TYPE_4__ port; scalar_t__ netcount; scalar_t__ dsr_chkcount; scalar_t__ ri_chkcount; scalar_t__ cts_chkcount; scalar_t__ dcd_chkcount; TYPE_1__ params; scalar_t__ tx_get; scalar_t__ tx_put; scalar_t__ tx_count; } ;
struct TYPE_16__ {int c_cflag; } ;
struct TYPE_17__ {TYPE_2__ termios; } ;
typedef  TYPE_5__ SLMP_INFO ;

/* Variables and functions */
 int CCTS ; 
 int CDCD ; 
 int CREAD ; 
 int /*<<< orphan*/  IE1 ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 int /*<<< orphan*/  async_mode (TYPE_5__*) ; 
 int /*<<< orphan*/  get_signals (TYPE_5__*) ; 
 int /*<<< orphan*/  hdlc_mode (TYPE_5__*) ; 
 int /*<<< orphan*/  rx_start (TYPE_5__*) ; 
 int /*<<< orphan*/  rx_stop (TYPE_5__*) ; 
 int /*<<< orphan*/  set_signals (TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_stop (TYPE_5__*) ; 
 int /*<<< orphan*/  write_reg (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void program_hw(SLMP_INFO *info)
{
	unsigned long flags;

	spin_lock_irqsave(&info->lock,flags);

	rx_stop(info);
	tx_stop(info);

	info->tx_count = info->tx_put = info->tx_get = 0;

	if (info->params.mode == MGSL_MODE_HDLC || info->netcount)
		hdlc_mode(info);
	else
		async_mode(info);

	set_signals(info);

	info->dcd_chkcount = 0;
	info->cts_chkcount = 0;
	info->ri_chkcount = 0;
	info->dsr_chkcount = 0;

	info->ie1_value |= (CDCD|CCTS);
	write_reg(info, IE1, info->ie1_value);

	get_signals(info);

	if (info->netcount || (info->port.tty && info->port.tty->termios.c_cflag & CREAD) )
		rx_start(info);

	spin_unlock_irqrestore(&info->lock,flags);
}