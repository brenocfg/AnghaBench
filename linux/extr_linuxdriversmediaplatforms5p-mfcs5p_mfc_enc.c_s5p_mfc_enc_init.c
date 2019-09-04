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
struct TYPE_3__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix_mp; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct s5p_mfc_ctx {void* dst_fmt; void* src_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_DST_FMT_ENC ; 
 int /*<<< orphan*/  DEF_SRC_FMT_ENC ; 
 int /*<<< orphan*/  MFC_FMT_ENC ; 
 int /*<<< orphan*/  MFC_FMT_RAW ; 
 void* find_format (struct v4l2_format*,int /*<<< orphan*/ ) ; 

void s5p_mfc_enc_init(struct s5p_mfc_ctx *ctx)
{
	struct v4l2_format f;
	f.fmt.pix_mp.pixelformat = DEF_SRC_FMT_ENC;
	ctx->src_fmt = find_format(&f, MFC_FMT_RAW);
	f.fmt.pix_mp.pixelformat = DEF_DST_FMT_ENC;
	ctx->dst_fmt = find_format(&f, MFC_FMT_ENC);
}