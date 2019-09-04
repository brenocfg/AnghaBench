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
struct vimc_pix_map {int /*<<< orphan*/  pixelformat; } ;
struct v4l2_fmtdesc {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vimc_pix_map* vimc_pix_map_by_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vimc_cap_enum_fmt_vid_cap(struct file *file, void *priv,
				     struct v4l2_fmtdesc *f)
{
	const struct vimc_pix_map *vpix = vimc_pix_map_by_index(f->index);

	if (!vpix)
		return -EINVAL;

	f->pixelformat = vpix->pixelformat;

	return 0;
}