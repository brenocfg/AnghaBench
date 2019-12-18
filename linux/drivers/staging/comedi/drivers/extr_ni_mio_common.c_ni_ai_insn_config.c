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
struct ni_private {unsigned int ai_calib_source; int /*<<< orphan*/  is_6143; int /*<<< orphan*/  is_611x; int /*<<< orphan*/  is_m_series; } ;
struct ni_board_struct {unsigned int ai_speed; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct ni_private* private; struct ni_board_struct* board_ptr; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_ALT_SOURCE 129 
#define  INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS 128 
 int /*<<< orphan*/  NI611X_CAL_GAIN_SEL_REG ; 
 int /*<<< orphan*/  NI6143_CALIB_CHAN_REG ; 
 unsigned int NI_M_CFG_BYPASS_AI_CAL_MASK ; 
 unsigned int ni_min_ai_scan_period_ns (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  ni_writeb (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ai_insn_config(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	const struct ni_board_struct *board = dev->board_ptr;
	struct ni_private *devpriv = dev->private;

	if (insn->n < 1)
		return -EINVAL;

	switch (data[0]) {
	case INSN_CONFIG_ALT_SOURCE:
		if (devpriv->is_m_series) {
			if (data[1] & ~NI_M_CFG_BYPASS_AI_CAL_MASK)
				return -EINVAL;
			devpriv->ai_calib_source = data[1];
		} else if (devpriv->is_6143) {
			unsigned int calib_source;

			calib_source = data[1] & 0xf;

			devpriv->ai_calib_source = calib_source;
			ni_writew(dev, calib_source, NI6143_CALIB_CHAN_REG);
		} else {
			unsigned int calib_source;
			unsigned int calib_source_adjust;

			calib_source = data[1] & 0xf;
			calib_source_adjust = (data[1] >> 4) & 0xff;

			if (calib_source >= 8)
				return -EINVAL;
			devpriv->ai_calib_source = calib_source;
			if (devpriv->is_611x) {
				ni_writeb(dev, calib_source_adjust,
					  NI611X_CAL_GAIN_SEL_REG);
			}
		}
		return 2;
	case INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS:
		/* we don't care about actual channels */
		/* data[3] : chanlist_len */
		data[1] = ni_min_ai_scan_period_ns(dev, data[3]);
		if (devpriv->is_611x || devpriv->is_6143)
			data[2] = 0; /* simultaneous output */
		else
			data[2] = board->ai_speed;
		return 0;
	default:
		break;
	}

	return -EINVAL;
}