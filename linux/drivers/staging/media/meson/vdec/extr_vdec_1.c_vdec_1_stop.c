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
struct amvdec_session {scalar_t__ priv; TYPE_1__* fmt_out; struct amvdec_core* core; } ;
struct amvdec_core {int /*<<< orphan*/  vdec_1_clk; int /*<<< orphan*/  regmap_ao; } ;
struct amvdec_codec_ops {int /*<<< orphan*/  (* stop ) (struct amvdec_session*) ;} ;
struct TYPE_2__ {struct amvdec_codec_ops* codec_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_RTI_GEN_PWR_ISO0 ; 
 int /*<<< orphan*/  AO_RTI_GEN_PWR_SLEEP0 ; 
 int /*<<< orphan*/  ASSIST_MBOX1_MASK ; 
 int BIT (int) ; 
 int /*<<< orphan*/  CPSR ; 
 int /*<<< orphan*/  DOS_MEM_PD_VDEC ; 
 int /*<<< orphan*/  DOS_SW_RESET0 ; 
 int /*<<< orphan*/  GEN_PWR_VDEC_1 ; 
 int /*<<< orphan*/  MPSR ; 
 int /*<<< orphan*/  amvdec_read_dos (struct amvdec_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amvdec_write_dos (struct amvdec_core*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct amvdec_session*) ; 

__attribute__((used)) static int vdec_1_stop(struct amvdec_session *sess)
{
	struct amvdec_core *core = sess->core;
	struct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	amvdec_write_dos(core, MPSR, 0);
	amvdec_write_dos(core, CPSR, 0);
	amvdec_write_dos(core, ASSIST_MBOX1_MASK, 0);

	amvdec_write_dos(core, DOS_SW_RESET0, BIT(12) | BIT(11));
	amvdec_write_dos(core, DOS_SW_RESET0, 0);
	amvdec_read_dos(core, DOS_SW_RESET0);

	/* enable vdec1 isolation */
	regmap_write(core->regmap_ao, AO_RTI_GEN_PWR_ISO0, 0xc0);
	/* power off vdec1 memories */
	amvdec_write_dos(core, DOS_MEM_PD_VDEC, 0xffffffff);
	/* power off vdec1 */
	regmap_update_bits(core->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VDEC_1, GEN_PWR_VDEC_1);

	clk_disable_unprepare(core->vdec_1_clk);

	if (sess->priv)
		codec_ops->stop(sess);

	return 0;
}