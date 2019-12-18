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
struct v4l2_fwht_pixfmt_info {int dummy; } ;
struct fwht_cframe_hdr {int /*<<< orphan*/  version; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int FWHT_FL_CHROMA_FULL_HEIGHT ; 
 unsigned int FWHT_FL_CHROMA_FULL_WIDTH ; 
 unsigned int FWHT_FL_COMPONENTS_NUM_MSK ; 
 unsigned int FWHT_FL_COMPONENTS_NUM_OFFSET ; 
 unsigned int FWHT_FL_PIXENC_MSK ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 struct v4l2_fwht_pixfmt_info const* v4l2_fwht_find_nth_fmt (unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct v4l2_fwht_pixfmt_info *
info_from_header(const struct fwht_cframe_hdr *p_hdr)
{
	unsigned int flags = ntohl(p_hdr->flags);
	unsigned int width_div = (flags & FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	unsigned int height_div = (flags & FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;
	unsigned int components_num = 3;
	unsigned int pixenc = 0;
	unsigned int version = ntohl(p_hdr->version);

	if (version >= 2) {
		components_num = 1 + ((flags & FWHT_FL_COMPONENTS_NUM_MSK) >>
				FWHT_FL_COMPONENTS_NUM_OFFSET);
		pixenc = (flags & FWHT_FL_PIXENC_MSK);
	}
	return v4l2_fwht_find_nth_fmt(width_div, height_div,
				     components_num, pixenc, 0);
}