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
typedef  int /*<<< orphan*/  u32 ;
struct s5p_jpeg_ctx {int subsampling; } ;
typedef  enum v4l2_jpeg_chroma_subsampling { ____Placeholder_v4l2_jpeg_chroma_subsampling } v4l2_jpeg_chroma_subsampling ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
#define  V4L2_JPEG_CHROMA_SUBSAMPLING_420 130 
#define  V4L2_JPEG_CHROMA_SUBSAMPLING_422 129 
#define  V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY 128 
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 int s5p_jpeg_get_dwngrd_sch_id_by_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * subs420_fourcc_dwngrd_schema ; 
 int /*<<< orphan*/ * subs422_fourcc_dwngrd_schema ; 

__attribute__((used)) static int s5p_jpeg_adjust_fourcc_to_subsampling(
					enum v4l2_jpeg_chroma_subsampling subs,
					u32 in_fourcc,
					u32 *out_fourcc,
					struct s5p_jpeg_ctx *ctx)
{
	int dwngrd_sch_id;

	if (ctx->subsampling != V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY) {
		dwngrd_sch_id =
			s5p_jpeg_get_dwngrd_sch_id_by_fourcc(in_fourcc);
		if (dwngrd_sch_id < 0)
			return -EINVAL;
	}

	switch (ctx->subsampling) {
	case V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY:
		*out_fourcc = V4L2_PIX_FMT_GREY;
		break;
	case V4L2_JPEG_CHROMA_SUBSAMPLING_420:
		if (dwngrd_sch_id >
				ARRAY_SIZE(subs420_fourcc_dwngrd_schema) - 1)
			return -EINVAL;
		*out_fourcc = subs420_fourcc_dwngrd_schema[dwngrd_sch_id];
		break;
	case V4L2_JPEG_CHROMA_SUBSAMPLING_422:
		if (dwngrd_sch_id >
				ARRAY_SIZE(subs422_fourcc_dwngrd_schema) - 1)
			return -EINVAL;
		*out_fourcc = subs422_fourcc_dwngrd_schema[dwngrd_sch_id];
		break;
	default:
		*out_fourcc = V4L2_PIX_FMT_GREY;
		break;
	}

	return 0;
}