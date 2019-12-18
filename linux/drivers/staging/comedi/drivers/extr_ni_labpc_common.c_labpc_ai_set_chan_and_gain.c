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
struct labpc_private {int /*<<< orphan*/  cmd1; int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct labpc_boardinfo {scalar_t__ is_labpc1200; } ;
struct comedi_device {struct labpc_private* private; struct labpc_boardinfo* board_ptr; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 unsigned int AREF_DIFF ; 
 int /*<<< orphan*/  CMD1_GAIN (unsigned int) ; 
 int /*<<< orphan*/  CMD1_MA (unsigned int) ; 
 int /*<<< orphan*/  CMD1_REG ; 
 int MODE_SINGLE_CHAN ; 
 int MODE_SINGLE_CHAN_INTERVAL ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void labpc_ai_set_chan_and_gain(struct comedi_device *dev,
				       enum scan_mode mode,
				       unsigned int chan,
				       unsigned int range,
				       unsigned int aref)
{
	const struct labpc_boardinfo *board = dev->board_ptr;
	struct labpc_private *devpriv = dev->private;

	if (board->is_labpc1200) {
		/*
		 * The LabPC-1200 boards do not have a gain
		 * of '0x10'. Skip the range values that would
		 * result in this gain.
		 */
		range += (range > 0) + (range > 7);
	}

	/* munge channel bits for differential/scan disabled mode */
	if ((mode == MODE_SINGLE_CHAN || mode == MODE_SINGLE_CHAN_INTERVAL) &&
	    aref == AREF_DIFF)
		chan *= 2;
	devpriv->cmd1 = CMD1_MA(chan);
	devpriv->cmd1 |= CMD1_GAIN(range);

	devpriv->write_byte(dev, devpriv->cmd1, CMD1_REG);
}