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
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int dummy; } ;

/* Variables and functions */
 int CX23885_AUD_MC_INT_CTRL_BITS ; 
 int /*<<< orphan*/  CX23885_AUD_MC_INT_MASK_REG ; 
 int CX23885_AUD_MC_INT_STAT_SHFT ; 
 int CX23885_PIN_CTRL_IRQ_AUD_STAT ; 
 int CX23885_PIN_CTRL_IRQ_IR_STAT ; 
 int /*<<< orphan*/  CX23885_PIN_CTRL_IRQ_REG ; 
 int CX23885_PIN_CTRL_IRQ_VID_STAT ; 
 int /*<<< orphan*/  CX25840_AUD_INT_CTRL_REG ; 
 int /*<<< orphan*/  CX25840_AUD_INT_STAT_REG ; 
 int /*<<< orphan*/  CX25840_IR_IRQEN_REG ; 
 int /*<<< orphan*/  CX25840_IR_STATS_REG ; 
 int CX25840_VID_INT_MASK_SHFT ; 
 int CX25840_VID_INT_STAT_BITS ; 
 int /*<<< orphan*/  CX25840_VID_INT_STAT_REG ; 
 int /*<<< orphan*/  cx25840_debug ; 
 int cx25840_ir_irq_handler (struct v4l2_subdev*,int,int*) ; 
 int cx25840_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int cx25840_read4 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_cx23885 (struct cx25840_state*) ; 
 scalar_t__ is_cx23887 (struct cx25840_state*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,...) ; 

__attribute__((used)) static int cx23885_irq_handler(struct v4l2_subdev *sd, u32 status,
			       bool *handled)
{
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *c = v4l2_get_subdevdata(sd);
	u8 irq_stat, aud_stat, aud_en, ir_stat, ir_en;
	u32 vid_stat, aud_mc_stat;
	bool block_handled;
	int ret = 0;

	irq_stat = cx25840_read(c, CX23885_PIN_CTRL_IRQ_REG);
	v4l_dbg(2, cx25840_debug, c, "AV Core IRQ status (entry): %s %s %s\n",
		irq_stat & CX23885_PIN_CTRL_IRQ_IR_STAT ? "ir" : "  ",
		irq_stat & CX23885_PIN_CTRL_IRQ_AUD_STAT ? "aud" : "   ",
		irq_stat & CX23885_PIN_CTRL_IRQ_VID_STAT ? "vid" : "   ");

	if ((is_cx23885(state) || is_cx23887(state))) {
		ir_stat = cx25840_read(c, CX25840_IR_STATS_REG);
		ir_en = cx25840_read(c, CX25840_IR_IRQEN_REG);
		v4l_dbg(2, cx25840_debug, c,
			"AV Core ir IRQ status: %#04x disables: %#04x\n",
			ir_stat, ir_en);
		if (irq_stat & CX23885_PIN_CTRL_IRQ_IR_STAT) {
			block_handled = false;
			ret = cx25840_ir_irq_handler(sd,
						     status, &block_handled);
			if (block_handled)
				*handled = true;
		}
	}

	aud_stat = cx25840_read(c, CX25840_AUD_INT_STAT_REG);
	aud_en = cx25840_read(c, CX25840_AUD_INT_CTRL_REG);
	v4l_dbg(2, cx25840_debug, c,
		"AV Core audio IRQ status: %#04x disables: %#04x\n",
		aud_stat, aud_en);
	aud_mc_stat = cx25840_read4(c, CX23885_AUD_MC_INT_MASK_REG);
	v4l_dbg(2, cx25840_debug, c,
		"AV Core audio MC IRQ status: %#06x enables: %#06x\n",
		aud_mc_stat >> CX23885_AUD_MC_INT_STAT_SHFT,
		aud_mc_stat & CX23885_AUD_MC_INT_CTRL_BITS);
	if (irq_stat & CX23885_PIN_CTRL_IRQ_AUD_STAT) {
		if (aud_stat) {
			cx25840_write(c, CX25840_AUD_INT_STAT_REG, aud_stat);
			*handled = true;
		}
	}

	vid_stat = cx25840_read4(c, CX25840_VID_INT_STAT_REG);
	v4l_dbg(2, cx25840_debug, c,
		"AV Core video IRQ status: %#06x disables: %#06x\n",
		vid_stat & CX25840_VID_INT_STAT_BITS,
		vid_stat >> CX25840_VID_INT_MASK_SHFT);
	if (irq_stat & CX23885_PIN_CTRL_IRQ_VID_STAT) {
		if (vid_stat & CX25840_VID_INT_STAT_BITS) {
			cx25840_write4(c, CX25840_VID_INT_STAT_REG, vid_stat);
			*handled = true;
		}
	}

	irq_stat = cx25840_read(c, CX23885_PIN_CTRL_IRQ_REG);
	v4l_dbg(2, cx25840_debug, c, "AV Core IRQ status (exit): %s %s %s\n",
		irq_stat & CX23885_PIN_CTRL_IRQ_IR_STAT ? "ir" : "  ",
		irq_stat & CX23885_PIN_CTRL_IRQ_AUD_STAT ? "aud" : "   ",
		irq_stat & CX23885_PIN_CTRL_IRQ_VID_STAT ? "vid" : "   ");

	return ret;
}