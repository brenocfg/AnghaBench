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
struct r100_cs_track_texture {int /*<<< orphan*/  compress_format; int /*<<< orphan*/  roundup_h; int /*<<< orphan*/  roundup_w; int /*<<< orphan*/  tex_coord_type; int /*<<< orphan*/  cpp; int /*<<< orphan*/  txdepth; int /*<<< orphan*/  num_levels; int /*<<< orphan*/  height_11; int /*<<< orphan*/  height; int /*<<< orphan*/  width_11; int /*<<< orphan*/  width; int /*<<< orphan*/  use_pitch; int /*<<< orphan*/  pitch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r100_cs_track_texture_print(struct r100_cs_track_texture *t)
{
	DRM_ERROR("pitch                      %d\n", t->pitch);
	DRM_ERROR("use_pitch                  %d\n", t->use_pitch);
	DRM_ERROR("width                      %d\n", t->width);
	DRM_ERROR("width_11                   %d\n", t->width_11);
	DRM_ERROR("height                     %d\n", t->height);
	DRM_ERROR("height_11                  %d\n", t->height_11);
	DRM_ERROR("num levels                 %d\n", t->num_levels);
	DRM_ERROR("depth                      %d\n", t->txdepth);
	DRM_ERROR("bpp                        %d\n", t->cpp);
	DRM_ERROR("coordinate type            %d\n", t->tex_coord_type);
	DRM_ERROR("width round to power of 2  %d\n", t->roundup_w);
	DRM_ERROR("height round to power of 2 %d\n", t->roundup_h);
	DRM_ERROR("compress format            %d\n", t->compress_format);
}