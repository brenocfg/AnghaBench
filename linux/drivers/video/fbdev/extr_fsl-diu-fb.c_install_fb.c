#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mfb_info {scalar_t__ index; int registered; int /*<<< orphan*/  id; int /*<<< orphan*/  pseudo_palette; struct fsl_diu_data* parent; } ;
struct fsl_diu_data {scalar_t__ has_edid; int /*<<< orphan*/  edid_data; } ;
struct fb_videomode {int flag; } ;
struct fb_monspecs {unsigned int modedb_len; int misc; struct fb_videomode* modedb; } ;
struct TYPE_4__ {int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  activate; } ;
struct fb_info {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmap; TYPE_1__ var; struct fb_monspecs monspecs; int /*<<< orphan*/  modelist; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; struct mfb_info* par; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct fb_videomode*) ; 
 int EINVAL ; 
 int FBINFO_DEFAULT ; 
 int FBINFO_PARTIAL_PAN_OK ; 
 int FBINFO_READS_FAST ; 
 int FBINFO_VIRTFB ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int FB_MISC_1ST_DETAIL ; 
 int FB_MODE_IS_FIRST ; 
 scalar_t__ PLANE0 ; 
 int /*<<< orphan*/  default_bpp ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_edid_to_monspecs (int /*<<< orphan*/ ,struct fb_monspecs*) ; 
 int fb_find_mode (TYPE_1__*,struct fb_info*,char const*,struct fb_videomode*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fb_mode ; 
 int /*<<< orphan*/  fb_videomode_to_modelist (struct fb_videomode*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_videomode_to_var (TYPE_1__*,struct fb_videomode*) ; 
 scalar_t__ fsl_diu_check_var (TYPE_1__*,struct fb_info*) ; 
 struct fb_videomode* fsl_diu_mode_db ; 
 int /*<<< orphan*/  fsl_diu_ops ; 
 scalar_t__ register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  unmap_video_memory (struct fb_info*) ; 

__attribute__((used)) static int install_fb(struct fb_info *info)
{
	int rc;
	struct mfb_info *mfbi = info->par;
	struct fsl_diu_data *data = mfbi->parent;
	const char *aoi_mode, *init_aoi_mode = "320x240";
	struct fb_videomode *db = fsl_diu_mode_db;
	unsigned int dbsize = ARRAY_SIZE(fsl_diu_mode_db);
	int has_default_mode = 1;

	info->var.activate = FB_ACTIVATE_NOW;
	info->fbops = &fsl_diu_ops;
	info->flags = FBINFO_DEFAULT | FBINFO_VIRTFB | FBINFO_PARTIAL_PAN_OK |
		FBINFO_READS_FAST;
	info->pseudo_palette = mfbi->pseudo_palette;

	rc = fb_alloc_cmap(&info->cmap, 16, 0);
	if (rc)
		return rc;

	if (mfbi->index == PLANE0) {
		if (data->has_edid) {
			/* Now build modedb from EDID */
			fb_edid_to_monspecs(data->edid_data, &info->monspecs);
			fb_videomode_to_modelist(info->monspecs.modedb,
						 info->monspecs.modedb_len,
						 &info->modelist);
			db = info->monspecs.modedb;
			dbsize = info->monspecs.modedb_len;
		}
		aoi_mode = fb_mode;
	} else {
		aoi_mode = init_aoi_mode;
	}
	rc = fb_find_mode(&info->var, info, aoi_mode, db, dbsize, NULL,
			  default_bpp);
	if (!rc) {
		/*
		 * For plane 0 we continue and look into
		 * driver's internal modedb.
		 */
		if ((mfbi->index == PLANE0) && data->has_edid)
			has_default_mode = 0;
		else
			return -EINVAL;
	}

	if (!has_default_mode) {
		rc = fb_find_mode(&info->var, info, aoi_mode, fsl_diu_mode_db,
			ARRAY_SIZE(fsl_diu_mode_db), NULL, default_bpp);
		if (rc)
			has_default_mode = 1;
	}

	/* Still not found, use preferred mode from database if any */
	if (!has_default_mode && info->monspecs.modedb) {
		struct fb_monspecs *specs = &info->monspecs;
		struct fb_videomode *modedb = &specs->modedb[0];

		/*
		 * Get preferred timing. If not found,
		 * first mode in database will be used.
		 */
		if (specs->misc & FB_MISC_1ST_DETAIL) {
			int i;

			for (i = 0; i < specs->modedb_len; i++) {
				if (specs->modedb[i].flag & FB_MODE_IS_FIRST) {
					modedb = &specs->modedb[i];
					break;
				}
			}
		}

		info->var.bits_per_pixel = default_bpp;
		fb_videomode_to_var(&info->var, modedb);
	}

	if (fsl_diu_check_var(&info->var, info)) {
		dev_err(info->dev, "fsl_diu_check_var failed\n");
		unmap_video_memory(info);
		fb_dealloc_cmap(&info->cmap);
		return -EINVAL;
	}

	if (register_framebuffer(info) < 0) {
		dev_err(info->dev, "register_framebuffer failed\n");
		unmap_video_memory(info);
		fb_dealloc_cmap(&info->cmap);
		return -EINVAL;
	}

	mfbi->registered = 1;
	dev_info(info->dev, "%s registered successfully\n", mfbi->id);

	return 0;
}