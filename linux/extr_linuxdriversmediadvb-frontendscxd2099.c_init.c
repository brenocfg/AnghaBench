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
typedef  int u32 ;
struct TYPE_2__ {int clock_mode; int bitrate; scalar_t__ polarity; } ;
struct cxd {int mode; int clk_reg_b; int clk_reg_f; int cammode; int /*<<< orphan*/  lock; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_mode (struct cxd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int write_reg (struct cxd*,int,int) ; 
 int write_regm (struct cxd*,int,int,int) ; 

__attribute__((used)) static int init(struct cxd *ci)
{
	int status;

	mutex_lock(&ci->lock);
	ci->mode = -1;
	do {
		status = write_reg(ci, 0x00, 0x00);
		if (status < 0)
			break;
		status = write_reg(ci, 0x01, 0x00);
		if (status < 0)
			break;
		status = write_reg(ci, 0x02, 0x10);
		if (status < 0)
			break;
		status = write_reg(ci, 0x03, 0x00);
		if (status < 0)
			break;
		status = write_reg(ci, 0x05, 0xFF);
		if (status < 0)
			break;
		status = write_reg(ci, 0x06, 0x1F);
		if (status < 0)
			break;
		status = write_reg(ci, 0x07, 0x1F);
		if (status < 0)
			break;
		status = write_reg(ci, 0x08, 0x28);
		if (status < 0)
			break;
		status = write_reg(ci, 0x14, 0x20);
		if (status < 0)
			break;

		/* TOSTRT = 8, Mode B (gated clock), falling Edge,
		 * Serial, POL=HIGH, MSB
		 */
		status = write_reg(ci, 0x0A, 0xA7);
		if (status < 0)
			break;

		status = write_reg(ci, 0x0B, 0x33);
		if (status < 0)
			break;
		status = write_reg(ci, 0x0C, 0x33);
		if (status < 0)
			break;

		status = write_regm(ci, 0x14, 0x00, 0x0F);
		if (status < 0)
			break;
		status = write_reg(ci, 0x15, ci->clk_reg_b);
		if (status < 0)
			break;
		status = write_regm(ci, 0x16, 0x00, 0x0F);
		if (status < 0)
			break;
		status = write_reg(ci, 0x17, ci->clk_reg_f);
		if (status < 0)
			break;

		if (ci->cfg.clock_mode == 2) {
			/* bitrate*2^13/ 72000 */
			u32 reg = ((ci->cfg.bitrate << 13) + 71999) / 72000;

			if (ci->cfg.polarity) {
				status = write_reg(ci, 0x09, 0x6f);
				if (status < 0)
					break;
			} else {
				status = write_reg(ci, 0x09, 0x6d);
				if (status < 0)
					break;
			}
			status = write_reg(ci, 0x20, 0x08);
			if (status < 0)
				break;
			status = write_reg(ci, 0x21, (reg >> 8) & 0xff);
			if (status < 0)
				break;
			status = write_reg(ci, 0x22, reg & 0xff);
			if (status < 0)
				break;
		} else if (ci->cfg.clock_mode == 1) {
			if (ci->cfg.polarity) {
				status = write_reg(ci, 0x09, 0x6f); /* D */
				if (status < 0)
					break;
			} else {
				status = write_reg(ci, 0x09, 0x6d);
				if (status < 0)
					break;
			}
			status = write_reg(ci, 0x20, 0x68);
			if (status < 0)
				break;
			status = write_reg(ci, 0x21, 0x00);
			if (status < 0)
				break;
			status = write_reg(ci, 0x22, 0x02);
			if (status < 0)
				break;
		} else {
			if (ci->cfg.polarity) {
				status = write_reg(ci, 0x09, 0x4f); /* C */
				if (status < 0)
					break;
			} else {
				status = write_reg(ci, 0x09, 0x4d);
				if (status < 0)
					break;
			}
			status = write_reg(ci, 0x20, 0x28);
			if (status < 0)
				break;
			status = write_reg(ci, 0x21, 0x00);
			if (status < 0)
				break;
			status = write_reg(ci, 0x22, 0x07);
			if (status < 0)
				break;
		}

		status = write_regm(ci, 0x20, 0x80, 0x80);
		if (status < 0)
			break;
		status = write_regm(ci, 0x03, 0x02, 0x02);
		if (status < 0)
			break;
		status = write_reg(ci, 0x01, 0x04);
		if (status < 0)
			break;
		status = write_reg(ci, 0x00, 0x31);
		if (status < 0)
			break;

		/* Put TS in bypass */
		status = write_regm(ci, 0x09, 0x08, 0x08);
		if (status < 0)
			break;
		ci->cammode = -1;
		cam_mode(ci, 0);
	} while (0);
	mutex_unlock(&ci->lock);

	return 0;
}