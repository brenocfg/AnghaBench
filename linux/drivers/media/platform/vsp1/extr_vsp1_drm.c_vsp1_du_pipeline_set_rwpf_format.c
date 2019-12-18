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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int num_planes; TYPE_1__* plane_fmt; } ;
struct vsp1_rwpf {TYPE_2__ format; struct vsp1_format_info const* fmtinfo; } ;
struct vsp1_format_info {int planes; int hsub; } ;
struct vsp1_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int bytesperline; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct vsp1_format_info* vsp1_get_format_info (struct vsp1_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsp1_du_pipeline_set_rwpf_format(struct vsp1_device *vsp1,
					    struct vsp1_rwpf *rwpf,
					    u32 pixelformat, unsigned int pitch)
{
	const struct vsp1_format_info *fmtinfo;
	unsigned int chroma_hsub;

	fmtinfo = vsp1_get_format_info(vsp1, pixelformat);
	if (!fmtinfo) {
		dev_dbg(vsp1->dev, "Unsupported pixel format %08x\n",
			pixelformat);
		return -EINVAL;
	}

	/*
	 * Only formats with three planes can affect the chroma planes pitch.
	 * All formats with two planes have a horizontal subsampling value of 2,
	 * but combine U and V in a single chroma plane, which thus results in
	 * the luma plane and chroma plane having the same pitch.
	 */
	chroma_hsub = (fmtinfo->planes == 3) ? fmtinfo->hsub : 1;

	rwpf->fmtinfo = fmtinfo;
	rwpf->format.num_planes = fmtinfo->planes;
	rwpf->format.plane_fmt[0].bytesperline = pitch;
	rwpf->format.plane_fmt[1].bytesperline = pitch / chroma_hsub;

	return 0;
}