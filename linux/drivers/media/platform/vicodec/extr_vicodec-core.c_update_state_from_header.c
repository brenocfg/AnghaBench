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
struct fwht_cframe_hdr {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {void* quantization; void* ycbcr_enc; void* xfer_func; void* colorspace; void* visible_height; void* visible_width; struct fwht_cframe_hdr header; } ;
struct vicodec_ctx {TYPE_1__ state; } ;

/* Variables and functions */
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_state_from_header(struct vicodec_ctx *ctx)
{
	const struct fwht_cframe_hdr *p_hdr = &ctx->state.header;

	ctx->state.visible_width = ntohl(p_hdr->width);
	ctx->state.visible_height = ntohl(p_hdr->height);
	ctx->state.colorspace = ntohl(p_hdr->colorspace);
	ctx->state.xfer_func = ntohl(p_hdr->xfer_func);
	ctx->state.ycbcr_enc = ntohl(p_hdr->ycbcr_enc);
	ctx->state.quantization = ntohl(p_hdr->quantization);
}