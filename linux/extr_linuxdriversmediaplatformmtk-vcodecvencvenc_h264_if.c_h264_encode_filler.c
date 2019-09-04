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
struct venc_h264_inst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int H264_FILLER_MARKER_SIZE ; 
 int /*<<< orphan*/  h264_filler_marker ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_h264_inst*,char*,int) ; 

__attribute__((used)) static void h264_encode_filler(struct venc_h264_inst *inst, void *buf,
			       int size)
{
	unsigned char *p = buf;

	if (size < H264_FILLER_MARKER_SIZE) {
		mtk_vcodec_err(inst, "filler size too small %d", size);
		return;
	}

	memcpy(p, h264_filler_marker, ARRAY_SIZE(h264_filler_marker));
	size -= H264_FILLER_MARKER_SIZE;
	p += H264_FILLER_MARKER_SIZE;
	memset(p, 0xff, size);
}