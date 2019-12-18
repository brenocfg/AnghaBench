#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vb2_dvb_frontends {int gate; } ;
struct TYPE_6__ {TYPE_4__* frontend; } ;
struct vb2_dvb_frontend {TYPE_2__ dvb; } ;
struct cx88_core {TYPE_3__* dvbdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (TYPE_4__*,int) ;} ;
struct TYPE_8__ {TYPE_1__ ops; } ;
struct TYPE_7__ {struct vb2_dvb_frontends frontends; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 
 struct vb2_dvb_frontend* vb2_dvb_get_frontend (struct vb2_dvb_frontends*,int) ; 

__attribute__((used)) static void cx88_dvb_gate_ctrl(struct cx88_core  *core, int open)
{
	struct vb2_dvb_frontends *f;
	struct vb2_dvb_frontend *fe;

	if (!core->dvbdev)
		return;

	f = &core->dvbdev->frontends;

	if (!f)
		return;

	if (f->gate <= 1) /* undefined or fe0 */
		fe = vb2_dvb_get_frontend(f, 1);
	else
		fe = vb2_dvb_get_frontend(f, f->gate);

	if (fe && fe->dvb.frontend && fe->dvb.frontend->ops.i2c_gate_ctrl)
		fe->dvb.frontend->ops.i2c_gate_ctrl(fe->dvb.frontend, open);
}