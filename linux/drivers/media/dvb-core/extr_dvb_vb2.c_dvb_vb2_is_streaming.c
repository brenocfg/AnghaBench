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
struct dvb_vb2_ctx {int state; } ;

/* Variables and functions */
 int DVB_VB2_STATE_STREAMON ; 

int dvb_vb2_is_streaming(struct dvb_vb2_ctx *ctx)
{
	return (ctx->state & DVB_VB2_STATE_STREAMON);
}