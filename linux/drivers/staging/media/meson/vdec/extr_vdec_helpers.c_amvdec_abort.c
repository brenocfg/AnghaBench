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
struct amvdec_session {TYPE_4__* m2m_ctx; TYPE_1__* core; } ;
struct TYPE_7__ {int /*<<< orphan*/  q; } ;
struct TYPE_6__ {int /*<<< orphan*/  q; } ;
struct TYPE_8__ {TYPE_3__ out_q_ctx; TYPE_2__ cap_q_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vb2_queue_error (int /*<<< orphan*/ *) ; 

void amvdec_abort(struct amvdec_session *sess)
{
	dev_info(sess->core->dev, "Aborting decoding session!\n");
	vb2_queue_error(&sess->m2m_ctx->cap_q_ctx.q);
	vb2_queue_error(&sess->m2m_ctx->out_q_ctx.q);
}