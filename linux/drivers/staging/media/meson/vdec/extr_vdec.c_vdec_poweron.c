#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct amvdec_session {TYPE_2__* core; TYPE_1__* fmt_out; } ;
struct amvdec_ops {int (* start ) (struct amvdec_session*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dos_parser_clk; int /*<<< orphan*/  dos_clk; } ;
struct TYPE_3__ {struct amvdec_ops* vdec_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esparser_power_up (struct amvdec_session*) ; 
 int stub1 (struct amvdec_session*) ; 

__attribute__((used)) static int vdec_poweron(struct amvdec_session *sess)
{
	int ret;
	struct amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;

	ret = clk_prepare_enable(sess->core->dos_parser_clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(sess->core->dos_clk);
	if (ret)
		goto disable_dos_parser;

	ret = vdec_ops->start(sess);
	if (ret)
		goto disable_dos;

	esparser_power_up(sess);

	return 0;

disable_dos:
	clk_disable_unprepare(sess->core->dos_clk);
disable_dos_parser:
	clk_disable_unprepare(sess->core->dos_parser_clk);

	return ret;
}