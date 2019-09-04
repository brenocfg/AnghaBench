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
struct vb2_buffer {int num_planes; int /*<<< orphan*/  index; } ;
struct s5p_mfc_fmt {int num_planes; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mfc_debug (int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int) ; 

__attribute__((used)) static int check_vb_with_fmt(struct s5p_mfc_fmt *fmt, struct vb2_buffer *vb)
{
	int i;

	if (!fmt)
		return -EINVAL;
	if (fmt->num_planes != vb->num_planes) {
		mfc_err("invalid plane number for the format\n");
		return -EINVAL;
	}
	for (i = 0; i < fmt->num_planes; i++) {
		dma_addr_t dma = vb2_dma_contig_plane_dma_addr(vb, i);
		if (!dma) {
			mfc_err("failed to get plane cookie\n");
			return -EINVAL;
		}
		mfc_debug(2, "index: %d, plane[%d] cookie: %pad\n",
			  vb->index, i, &dma);
	}
	return 0;
}