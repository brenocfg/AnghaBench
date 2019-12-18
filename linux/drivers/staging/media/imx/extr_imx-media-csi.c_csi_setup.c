#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_rect {int width; int height; } ;
struct v4l2_mbus_framefmt {int width; } ;
struct v4l2_mbus_config {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct imx_media_pixfmt {int cycles; } ;
struct TYPE_10__ {int width; int height; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {TYPE_2__ mipi_csi2; TYPE_1__ parallel; } ;
struct TYPE_12__ {TYPE_3__ bus; int /*<<< orphan*/  bus_type; } ;
struct csi_priv {size_t active_output_pad; scalar_t__ dest; int /*<<< orphan*/  csi; TYPE_5__* skip; TYPE_4__ compose; struct v4l2_rect crop; TYPE_6__ upstream_ep; struct v4l2_mbus_framefmt* format_mbus; struct imx_media_pixfmt** cc; } ;
struct TYPE_11__ {scalar_t__ max_ratio; int /*<<< orphan*/  skip_smfc; } ;

/* Variables and functions */
 size_t CSI_SINK_PAD ; 
 scalar_t__ IPU_CSI_DEST_IDMAC ; 
 int /*<<< orphan*/  ipu_csi_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_init_interface (int /*<<< orphan*/ ,struct v4l2_mbus_config*,struct v4l2_mbus_framefmt*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  ipu_csi_set_dest (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipu_csi_set_downsize (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ipu_csi_set_skip_smfc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_set_window (int /*<<< orphan*/ ,struct v4l2_rect*) ; 
 scalar_t__ is_parallel_bus (TYPE_6__*) ; 

__attribute__((used)) static int csi_setup(struct csi_priv *priv)
{
	struct v4l2_mbus_framefmt *infmt, *outfmt;
	const struct imx_media_pixfmt *incc;
	struct v4l2_mbus_config mbus_cfg;
	struct v4l2_mbus_framefmt if_fmt;
	struct v4l2_rect crop;

	infmt = &priv->format_mbus[CSI_SINK_PAD];
	incc = priv->cc[CSI_SINK_PAD];
	outfmt = &priv->format_mbus[priv->active_output_pad];

	/* compose mbus_config from the upstream endpoint */
	mbus_cfg.type = priv->upstream_ep.bus_type;
	mbus_cfg.flags = is_parallel_bus(&priv->upstream_ep) ?
		priv->upstream_ep.bus.parallel.flags :
		priv->upstream_ep.bus.mipi_csi2.flags;

	if_fmt = *infmt;
	crop = priv->crop;

	/*
	 * if cycles is set, we need to handle this over multiple cycles as
	 * generic/bayer data
	 */
	if (is_parallel_bus(&priv->upstream_ep) && incc->cycles) {
		if_fmt.width *= incc->cycles;
		crop.width *= incc->cycles;
	}

	ipu_csi_set_window(priv->csi, &crop);

	ipu_csi_set_downsize(priv->csi,
			     priv->crop.width == 2 * priv->compose.width,
			     priv->crop.height == 2 * priv->compose.height);

	ipu_csi_init_interface(priv->csi, &mbus_cfg, &if_fmt, outfmt);

	ipu_csi_set_dest(priv->csi, priv->dest);

	if (priv->dest == IPU_CSI_DEST_IDMAC)
		ipu_csi_set_skip_smfc(priv->csi, priv->skip->skip_smfc,
				      priv->skip->max_ratio - 1, 0);

	ipu_csi_dump(priv->csi);

	return 0;
}