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
struct amvdec_session {struct amvdec_core* core; } ;
struct amvdec_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOS_GEN_CTRL0 ; 
 int /*<<< orphan*/  VLD_MEM_VIFIFO_BUF_CNTL ; 
 int /*<<< orphan*/  amvdec_clear_dos_bits (struct amvdec_core*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amvdec_write_dos (struct amvdec_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vdec_1_conf_esparser(struct amvdec_session *sess)
{
	struct amvdec_core *core = sess->core;

	/* VDEC_1 specific ESPARSER stuff */
	amvdec_write_dos(core, DOS_GEN_CTRL0, 0);
	amvdec_write_dos(core, VLD_MEM_VIFIFO_BUF_CNTL, 1);
	amvdec_clear_dos_bits(core, VLD_MEM_VIFIFO_BUF_CNTL, 1);
}