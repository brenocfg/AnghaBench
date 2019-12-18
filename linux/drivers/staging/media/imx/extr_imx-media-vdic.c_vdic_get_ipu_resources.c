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
struct vdic_priv {int /*<<< orphan*/  sd; struct ipuv3_channel* vdi_in_ch_n; int /*<<< orphan*/  ipu; struct ipuv3_channel* vdi_in_ch; struct ipuv3_channel* vdi_in_ch_p; int /*<<< orphan*/  csi_direct; struct ipuv3_channel* vdi; } ;
struct ipuv3_channel {int dummy; } ;
typedef  struct ipuv3_channel ipu_vdi ;

/* Variables and functions */
 int IPUV3_CHANNEL_MEM_VDI_CUR ; 
 int IPUV3_CHANNEL_MEM_VDI_NEXT ; 
 int IPUV3_CHANNEL_MEM_VDI_PREV ; 
 scalar_t__ IS_ERR (struct ipuv3_channel*) ; 
 int PTR_ERR (struct ipuv3_channel*) ; 
 struct ipuv3_channel* ipu_idmac_get (int /*<<< orphan*/ ,int) ; 
 struct ipuv3_channel* ipu_vdi_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  vdic_put_ipu_resources (struct vdic_priv*) ; 

__attribute__((used)) static int vdic_get_ipu_resources(struct vdic_priv *priv)
{
	int ret, err_chan;
	struct ipuv3_channel *ch;
	struct ipu_vdi *vdi;

	vdi = ipu_vdi_get(priv->ipu);
	if (IS_ERR(vdi)) {
		v4l2_err(&priv->sd, "failed to get VDIC\n");
		ret = PTR_ERR(vdi);
		goto out;
	}
	priv->vdi = vdi;

	if (!priv->csi_direct) {
		ch = ipu_idmac_get(priv->ipu, IPUV3_CHANNEL_MEM_VDI_PREV);
		if (IS_ERR(ch)) {
			err_chan = IPUV3_CHANNEL_MEM_VDI_PREV;
			ret = PTR_ERR(ch);
			goto out_err_chan;
		}
		priv->vdi_in_ch_p = ch;

		ch = ipu_idmac_get(priv->ipu, IPUV3_CHANNEL_MEM_VDI_CUR);
		if (IS_ERR(ch)) {
			err_chan = IPUV3_CHANNEL_MEM_VDI_CUR;
			ret = PTR_ERR(ch);
			goto out_err_chan;
		}
		priv->vdi_in_ch = ch;

		ch = ipu_idmac_get(priv->ipu, IPUV3_CHANNEL_MEM_VDI_NEXT);
		if (IS_ERR(ch)) {
			err_chan = IPUV3_CHANNEL_MEM_VDI_NEXT;
			ret = PTR_ERR(ch);
			goto out_err_chan;
		}
		priv->vdi_in_ch_n = ch;
	}

	return 0;

out_err_chan:
	v4l2_err(&priv->sd, "could not get IDMAC channel %u\n", err_chan);
out:
	vdic_put_ipu_resources(priv);
	return ret;
}