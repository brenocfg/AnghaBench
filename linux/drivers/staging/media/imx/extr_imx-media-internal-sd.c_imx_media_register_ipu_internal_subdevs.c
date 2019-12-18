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
struct v4l2_subdev {scalar_t__ grp_id; TYPE_1__* dev; } ;
struct ipu_soc {int dummy; } ;
struct internal_subdev {scalar_t__ grp_id; int /*<<< orphan*/  (* sync_unregister ) (struct v4l2_subdev*) ;struct v4l2_subdev* (* sync_register ) (int /*<<< orphan*/ *,struct device*,struct ipu_soc*,scalar_t__) ;} ;
struct imx_media_dev {int /*<<< orphan*/  mutex; struct v4l2_subdev*** sync_sd; int /*<<< orphan*/  v4l2_dev; struct ipu_soc** ipu; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct v4l2_subdev*) ; 
 int NUM_IPU_SUBDEVS ; 
 int PTR_ERR (struct v4l2_subdev*) ; 
 int create_ipu_internal_links (struct imx_media_dev*,struct internal_subdev const*,struct v4l2_subdev*,int) ; 
 struct ipu_soc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  imx_media_unregister_ipu_internal_subdevs (struct imx_media_dev*) ; 
 struct internal_subdev* int_subdev ; 
 int ipu_get_num (struct ipu_soc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* stub1 (int /*<<< orphan*/ *,struct device*,struct ipu_soc*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 

int imx_media_register_ipu_internal_subdevs(struct imx_media_dev *imxmd,
					    struct v4l2_subdev *csi)
{
	struct device *ipu_dev = csi->dev->parent;
	const struct internal_subdev *intsd;
	struct v4l2_subdev *sd;
	struct ipu_soc *ipu;
	int i, ipu_id, ret;

	ipu = dev_get_drvdata(ipu_dev);
	if (!ipu) {
		v4l2_err(&imxmd->v4l2_dev, "invalid IPU device!\n");
		return -ENODEV;
	}

	ipu_id = ipu_get_num(ipu);
	if (ipu_id > 1) {
		v4l2_err(&imxmd->v4l2_dev, "invalid IPU id %d!\n", ipu_id);
		return -ENODEV;
	}

	mutex_lock(&imxmd->mutex);

	/* record this IPU */
	if (!imxmd->ipu[ipu_id])
		imxmd->ipu[ipu_id] = ipu;

	/* register the synchronous subdevs */
	for (i = 0; i < NUM_IPU_SUBDEVS; i++) {
		intsd = &int_subdev[i];

		sd = imxmd->sync_sd[ipu_id][i];

		/*
		 * skip if this sync subdev already registered or its
		 * not a sync subdev (one of the CSIs)
		 */
		if (sd || !intsd->sync_register)
			continue;

		mutex_unlock(&imxmd->mutex);
		sd = intsd->sync_register(&imxmd->v4l2_dev, ipu_dev, ipu,
					  intsd->grp_id);
		mutex_lock(&imxmd->mutex);
		if (IS_ERR(sd)) {
			ret = PTR_ERR(sd);
			goto err_unwind;
		}

		imxmd->sync_sd[ipu_id][i] = sd;
	}

	/*
	 * all the sync subdevs are registered, create the media links
	 * between them.
	 */
	for (i = 0; i < NUM_IPU_SUBDEVS; i++) {
		intsd = &int_subdev[i];

		if (intsd->grp_id == csi->grp_id) {
			sd = csi;
		} else {
			sd = imxmd->sync_sd[ipu_id][i];
			if (!sd)
				continue;
		}

		ret = create_ipu_internal_links(imxmd, intsd, sd, ipu_id);
		if (ret) {
			mutex_unlock(&imxmd->mutex);
			imx_media_unregister_ipu_internal_subdevs(imxmd);
			return ret;
		}
	}

	mutex_unlock(&imxmd->mutex);
	return 0;

err_unwind:
	while (--i >= 0) {
		intsd = &int_subdev[i];
		sd = imxmd->sync_sd[ipu_id][i];
		if (!sd || !intsd->sync_unregister)
			continue;
		mutex_unlock(&imxmd->mutex);
		intsd->sync_unregister(sd);
		mutex_lock(&imxmd->mutex);
	}

	mutex_unlock(&imxmd->mutex);
	return ret;
}