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
struct ipu_plane {int dma; scalar_t__ dp_flow; void* dp; int /*<<< orphan*/  ipu; void* dmfc; void* alpha_ch; void* ipu_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int ipu_channel_alpha_channel (int) ; 
 void* ipu_dmfc_get (int /*<<< orphan*/ ,int) ; 
 void* ipu_dp_get (int /*<<< orphan*/ ,scalar_t__) ; 
 void* ipu_idmac_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_plane_put_resources (struct ipu_plane*) ; 

int ipu_plane_get_resources(struct ipu_plane *ipu_plane)
{
	int ret;
	int alpha_ch;

	ipu_plane->ipu_ch = ipu_idmac_get(ipu_plane->ipu, ipu_plane->dma);
	if (IS_ERR(ipu_plane->ipu_ch)) {
		ret = PTR_ERR(ipu_plane->ipu_ch);
		DRM_ERROR("failed to get idmac channel: %d\n", ret);
		return ret;
	}

	alpha_ch = ipu_channel_alpha_channel(ipu_plane->dma);
	if (alpha_ch >= 0) {
		ipu_plane->alpha_ch = ipu_idmac_get(ipu_plane->ipu, alpha_ch);
		if (IS_ERR(ipu_plane->alpha_ch)) {
			ret = PTR_ERR(ipu_plane->alpha_ch);
			DRM_ERROR("failed to get alpha idmac channel %d: %d\n",
				  alpha_ch, ret);
			return ret;
		}
	}

	ipu_plane->dmfc = ipu_dmfc_get(ipu_plane->ipu, ipu_plane->dma);
	if (IS_ERR(ipu_plane->dmfc)) {
		ret = PTR_ERR(ipu_plane->dmfc);
		DRM_ERROR("failed to get dmfc: ret %d\n", ret);
		goto err_out;
	}

	if (ipu_plane->dp_flow >= 0) {
		ipu_plane->dp = ipu_dp_get(ipu_plane->ipu, ipu_plane->dp_flow);
		if (IS_ERR(ipu_plane->dp)) {
			ret = PTR_ERR(ipu_plane->dp);
			DRM_ERROR("failed to get dp flow: %d\n", ret);
			goto err_out;
		}
	}

	return 0;
err_out:
	ipu_plane_put_resources(ipu_plane);

	return ret;
}