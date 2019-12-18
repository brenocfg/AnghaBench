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
struct amvdec_session {TYPE_1__* fmt_out; } ;
struct amvdec_codec_ops {scalar_t__ recycle; scalar_t__ can_recycle; } ;
struct TYPE_2__ {struct amvdec_codec_ops* codec_ops; } ;

/* Variables and functions */

__attribute__((used)) static int vdec_codec_needs_recycle(struct amvdec_session *sess)
{
	struct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	return codec_ops->can_recycle && codec_ops->recycle;
}