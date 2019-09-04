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
struct sti_private {struct sti_compositor* compo; } ;
struct sti_compositor_subdev_descriptor {int type; scalar_t__ offset; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {unsigned int nb_subdev; struct sti_compositor_subdev_descriptor* subdev_desc; } ;
struct sti_compositor {int /*<<< orphan*/ * mixer; scalar_t__ regs; int /*<<< orphan*/  dev; int /*<<< orphan*/ * vid; TYPE_1__ data; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int irq_enabled; struct sti_private* dev_private; } ;
struct device {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
#define  STI_CURSOR_SUBDEV 132 
#define  STI_GPD_SUBDEV 131 
#define  STI_MIXER_AUX_SUBDEV 130 
#define  STI_MIXER_MAIN_SUBDEV 129 
#define  STI_VID_SUBDEV 128 
 struct sti_compositor* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_vblank_init (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  sti_crtc_init (struct drm_device*,int /*<<< orphan*/ ,struct drm_plane*,struct drm_plane*) ; 
 struct drm_plane* sti_cursor_create (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct drm_plane* sti_gdp_create (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  sti_mixer_create (int /*<<< orphan*/ ,struct drm_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sti_vid_create (int /*<<< orphan*/ ,struct drm_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sti_compositor_bind(struct device *dev,
			       struct device *master,
			       void *data)
{
	struct sti_compositor *compo = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	unsigned int i, mixer_id = 0, vid_id = 0, crtc_id = 0;
	struct sti_private *dev_priv = drm_dev->dev_private;
	struct drm_plane *cursor = NULL;
	struct drm_plane *primary = NULL;
	struct sti_compositor_subdev_descriptor *desc = compo->data.subdev_desc;
	unsigned int array_size = compo->data.nb_subdev;

	dev_priv->compo = compo;

	/* Register mixer subdev and video subdev first */
	for (i = 0; i < array_size; i++) {
		switch (desc[i].type) {
		case STI_VID_SUBDEV:
			compo->vid[vid_id++] =
			    sti_vid_create(compo->dev, drm_dev, desc[i].id,
					   compo->regs + desc[i].offset);
			break;
		case STI_MIXER_MAIN_SUBDEV:
		case STI_MIXER_AUX_SUBDEV:
			compo->mixer[mixer_id++] =
			    sti_mixer_create(compo->dev, drm_dev, desc[i].id,
					     compo->regs + desc[i].offset);
			break;
		case STI_GPD_SUBDEV:
		case STI_CURSOR_SUBDEV:
			/* Nothing to do, wait for the second round */
			break;
		default:
			DRM_ERROR("Unknown subdev component type\n");
			return 1;
		}
	}

	/* Register the other subdevs, create crtc and planes */
	for (i = 0; i < array_size; i++) {
		enum drm_plane_type plane_type = DRM_PLANE_TYPE_OVERLAY;

		if (crtc_id < mixer_id)
			plane_type = DRM_PLANE_TYPE_PRIMARY;

		switch (desc[i].type) {
		case STI_MIXER_MAIN_SUBDEV:
		case STI_MIXER_AUX_SUBDEV:
		case STI_VID_SUBDEV:
			/* Nothing to do, already done at the first round */
			break;
		case STI_CURSOR_SUBDEV:
			cursor = sti_cursor_create(drm_dev, compo->dev,
						   desc[i].id,
						   compo->regs + desc[i].offset,
						   1);
			if (!cursor) {
				DRM_ERROR("Can't create CURSOR plane\n");
				break;
			}
			break;
		case STI_GPD_SUBDEV:
			primary = sti_gdp_create(drm_dev, compo->dev,
						 desc[i].id,
						 compo->regs + desc[i].offset,
						 (1 << mixer_id) - 1,
						 plane_type);
			if (!primary) {
				DRM_ERROR("Can't create GDP plane\n");
				break;
			}
			break;
		default:
			DRM_ERROR("Unknown subdev component type\n");
			return 1;
		}

		/* The first planes are reserved for primary planes*/
		if (crtc_id < mixer_id && primary) {
			sti_crtc_init(drm_dev, compo->mixer[crtc_id],
				      primary, cursor);
			crtc_id++;
			cursor = NULL;
			primary = NULL;
		}
	}

	drm_vblank_init(drm_dev, crtc_id);
	/* Allow usage of vblank without having to call drm_irq_install */
	drm_dev->irq_enabled = 1;

	return 0;
}