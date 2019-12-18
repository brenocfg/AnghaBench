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
struct fwht_cframe_hdr {void* quantization; void* ycbcr_enc; void* xfer_func; void* colorspace; void* flags; void* height; void* width; void* version; int /*<<< orphan*/  magic2; int /*<<< orphan*/  magic1; } ;
struct TYPE_2__ {struct fwht_cframe_hdr header; } ;
struct vicodec_ctx {TYPE_1__ state; } ;
struct v4l2_ctrl_fwht_params {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  flags; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWHT_MAGIC1 ; 
 int /*<<< orphan*/  FWHT_MAGIC2 ; 
 void* htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_header_from_stateless_params(struct vicodec_ctx *ctx,
						const struct v4l2_ctrl_fwht_params *params)
{
	struct fwht_cframe_hdr *p_hdr = &ctx->state.header;

	p_hdr->magic1 = FWHT_MAGIC1;
	p_hdr->magic2 = FWHT_MAGIC2;
	p_hdr->version = htonl(params->version);
	p_hdr->width = htonl(params->width);
	p_hdr->height = htonl(params->height);
	p_hdr->flags = htonl(params->flags);
	p_hdr->colorspace = htonl(params->colorspace);
	p_hdr->xfer_func = htonl(params->xfer_func);
	p_hdr->ycbcr_enc = htonl(params->ycbcr_enc);
	p_hdr->quantization = htonl(params->quantization);
}