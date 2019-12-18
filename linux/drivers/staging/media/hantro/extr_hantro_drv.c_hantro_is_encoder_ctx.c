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
struct hantro_ctx {scalar_t__ buf_finish; } ;

/* Variables and functions */
 scalar_t__ hantro_enc_buf_finish ; 

bool hantro_is_encoder_ctx(const struct hantro_ctx *ctx)
{
	return ctx->buf_finish == hantro_enc_buf_finish;
}