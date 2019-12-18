#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rcar_du_crtc {TYPE_4__* vsp; } ;
typedef  enum vsp1_du_crc_source { ____Placeholder_vsp1_du_crc_source } vsp1_du_crc_source ;
struct TYPE_8__ {unsigned int num_planes; TYPE_3__* planes; } ;
struct TYPE_5__ {unsigned int id; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct TYPE_7__ {TYPE_2__ plane; } ;

/* Variables and functions */
 int EINVAL ; 
 int VSP1_DU_CRC_NONE ; 
 int VSP1_DU_CRC_OUTPUT ; 
 int VSP1_DU_CRC_PLANE ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strstarts (char const*,char*) ; 

__attribute__((used)) static int rcar_du_crtc_parse_crc_source(struct rcar_du_crtc *rcrtc,
					 const char *source_name,
					 enum vsp1_du_crc_source *source)
{
	unsigned int index;
	int ret;

	/*
	 * Parse the source name. Supported values are "plane%u" to compute the
	 * CRC on an input plane (%u is the plane ID), and "auto" to compute the
	 * CRC on the composer (VSP) output.
	 */

	if (!source_name) {
		*source = VSP1_DU_CRC_NONE;
		return 0;
	} else if (!strcmp(source_name, "auto")) {
		*source = VSP1_DU_CRC_OUTPUT;
		return 0;
	} else if (strstarts(source_name, "plane")) {
		unsigned int i;

		*source = VSP1_DU_CRC_PLANE;

		ret = kstrtouint(source_name + strlen("plane"), 10, &index);
		if (ret < 0)
			return ret;

		for (i = 0; i < rcrtc->vsp->num_planes; ++i) {
			if (index == rcrtc->vsp->planes[i].plane.base.id)
				return i;
		}
	}

	return -EINVAL;
}