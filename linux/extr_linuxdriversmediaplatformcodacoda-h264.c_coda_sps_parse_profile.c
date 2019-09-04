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
typedef  int /*<<< orphan*/  u8 ;
struct vb2_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  h264_level_idc; int /*<<< orphan*/  h264_profile_idc; } ;
struct coda_ctx {TYPE_1__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * coda_find_nal_header (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

int coda_sps_parse_profile(struct coda_ctx *ctx, struct vb2_buffer *vb)
{
	const u8 *buf = vb2_plane_vaddr(vb, 0);
	const u8 *end = buf + vb2_get_plane_payload(vb, 0);

	/* Find SPS header */
	do {
		buf = coda_find_nal_header(buf, end);
		if (!buf)
			return -EINVAL;
	} while ((*buf++ & 0x1f) != 0x7);

	ctx->params.h264_profile_idc = buf[0];
	ctx->params.h264_level_idc = buf[2];

	return 0;
}