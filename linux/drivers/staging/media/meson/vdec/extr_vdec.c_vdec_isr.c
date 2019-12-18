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
struct amvdec_session {TYPE_2__* fmt_out; int /*<<< orphan*/  last_irq_jiffies; } ;
struct amvdec_core {struct amvdec_session* cur_sess; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* codec_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* isr ) (struct amvdec_session*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int /*<<< orphan*/  stub1 (struct amvdec_session*) ; 

__attribute__((used)) static irqreturn_t vdec_isr(int irq, void *data)
{
	struct amvdec_core *core = data;
	struct amvdec_session *sess = core->cur_sess;

	sess->last_irq_jiffies = get_jiffies_64();

	return sess->fmt_out->codec_ops->isr(sess);
}