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
struct amvdec_session {scalar_t__ pixfmt_cap; TYPE_1__* fmt_out; struct amvdec_core* core; } ;
struct amvdec_core {int /*<<< orphan*/  regmap_ao; int /*<<< orphan*/  vdec_1_clk; } ;
struct amvdec_codec_ops {int (* start ) (struct amvdec_session*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  firmware_path; struct amvdec_codec_ops* codec_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_RTI_GEN_PWR_ISO0 ; 
 int /*<<< orphan*/  AO_RTI_GEN_PWR_SLEEP0 ; 
 int /*<<< orphan*/  ASSIST_MBOX1_CLR_REG ; 
 int /*<<< orphan*/  ASSIST_MBOX1_MASK ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DOS_GCLK_EN0 ; 
 int /*<<< orphan*/  DOS_MEM_PD_VDEC ; 
 int /*<<< orphan*/  DOS_SW_RESET0 ; 
 int /*<<< orphan*/  DOS_VDEC_MCRCC_STALL_CTRL ; 
 int /*<<< orphan*/  GCLK_EN ; 
 int /*<<< orphan*/  GEN_PWR_VDEC_1 ; 
 int /*<<< orphan*/  MDEC_PIC_DC_CTRL ; 
 int /*<<< orphan*/  MPSR ; 
 scalar_t__ V4L2_PIX_FMT_NV12M ; 
 int /*<<< orphan*/  amvdec_clear_dos_bits (struct amvdec_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amvdec_write_dos (struct amvdec_core*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amvdec_write_dos_bits (struct amvdec_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct amvdec_session*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int vdec_1_load_firmware (struct amvdec_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdec_1_stbuf_power_up (struct amvdec_session*) ; 
 int /*<<< orphan*/  vdec_1_stop (struct amvdec_session*) ; 

__attribute__((used)) static int vdec_1_start(struct amvdec_session *sess)
{
	int ret;
	struct amvdec_core *core = sess->core;
	struct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	/* Configure the vdec clk to the maximum available */
	clk_set_rate(core->vdec_1_clk, 666666666);
	ret = clk_prepare_enable(core->vdec_1_clk);
	if (ret)
		return ret;

	/* Enable power for VDEC_1 */
	regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VDEC_1, 0);
	usleep_range(10, 20);

	/* Reset VDEC1 */
	amvdec_write_dos(core, DOS_SW_RESET0, 0xfffffffc);
	amvdec_write_dos(core, DOS_SW_RESET0, 0x00000000);

	amvdec_write_dos(core, DOS_GCLK_EN0, 0x3ff);

	/* enable VDEC Memories */
	amvdec_write_dos(core, DOS_MEM_PD_VDEC, 0);
	/* Remove VDEC1 Isolation */
	regmap_write(core->regmap_ao, AO_RTI_GEN_PWR_ISO0, 0);
	/* Reset DOS top registers */
	amvdec_write_dos(core, DOS_VDEC_MCRCC_STALL_CTRL, 0);

	amvdec_write_dos(core, GCLK_EN, 0x3ff);
	amvdec_clear_dos_bits(core, MDEC_PIC_DC_CTRL, BIT(31));

	vdec_1_stbuf_power_up(sess);

	ret = vdec_1_load_firmware(sess, sess->fmt_out->firmware_path);
	if (ret)
		goto stop;

	ret = codec_ops->start(sess);
	if (ret)
		goto stop;

	/* Enable IRQ */
	amvdec_write_dos(core, ASSIST_MBOX1_CLR_REG, 1);
	amvdec_write_dos(core, ASSIST_MBOX1_MASK, 1);

	/* Enable 2-plane output */
	if (sess->pixfmt_cap == V4L2_PIX_FMT_NV12M)
		amvdec_write_dos_bits(core, MDEC_PIC_DC_CTRL, BIT(17));
	else
		amvdec_clear_dos_bits(core, MDEC_PIC_DC_CTRL, BIT(17));

	/* Enable firmware processor */
	amvdec_write_dos(core, MPSR, 1);
	/* Let the firmware settle */
	usleep_range(10, 20);

	return 0;

stop:
	vdec_1_stop(sess);
	return ret;
}