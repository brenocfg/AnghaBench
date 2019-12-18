#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct nv50_mstm {TYPE_12__** msto; TYPE_3__* outp; } ;
struct TYPE_19__ {int /*<<< orphan*/  base; TYPE_4__* funcs; } ;
struct nv50_mstc {TYPE_6__ connector; struct drm_dp_mst_port* port; struct nv50_mstm* mstm; } ;
struct drm_dp_mst_port {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  tile_property; int /*<<< orphan*/  path_property; } ;
struct drm_device {TYPE_5__ mode_config; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* reset ) (TYPE_6__*) ;} ;
struct TYPE_14__ {struct drm_device* dev; } ;
struct TYPE_15__ {TYPE_1__ base; } ;
struct TYPE_16__ {TYPE_2__ base; } ;
struct TYPE_13__ {int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_12__**) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DisplayPort ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_set_path_property (TYPE_6__*,char const*) ; 
 int /*<<< orphan*/  drm_dp_mst_get_port_malloc (struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nv50_mstc*) ; 
 struct nv50_mstc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_conn_attach_properties (TYPE_6__*) ; 
 int /*<<< orphan*/  nv50_mstc ; 
 int /*<<< orphan*/  nv50_mstc_help ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 

__attribute__((used)) static int
nv50_mstc_new(struct nv50_mstm *mstm, struct drm_dp_mst_port *port,
	      const char *path, struct nv50_mstc **pmstc)
{
	struct drm_device *dev = mstm->outp->base.base.dev;
	struct nv50_mstc *mstc;
	int ret, i;

	if (!(mstc = *pmstc = kzalloc(sizeof(*mstc), GFP_KERNEL)))
		return -ENOMEM;
	mstc->mstm = mstm;
	mstc->port = port;

	ret = drm_connector_init(dev, &mstc->connector, &nv50_mstc,
				 DRM_MODE_CONNECTOR_DisplayPort);
	if (ret) {
		kfree(*pmstc);
		*pmstc = NULL;
		return ret;
	}

	drm_connector_helper_add(&mstc->connector, &nv50_mstc_help);

	mstc->connector.funcs->reset(&mstc->connector);
	nouveau_conn_attach_properties(&mstc->connector);

	for (i = 0; i < ARRAY_SIZE(mstm->msto) && mstm->msto[i]; i++)
		drm_connector_attach_encoder(&mstc->connector, &mstm->msto[i]->encoder);

	drm_object_attach_property(&mstc->connector.base, dev->mode_config.path_property, 0);
	drm_object_attach_property(&mstc->connector.base, dev->mode_config.tile_property, 0);
	drm_connector_set_path_property(&mstc->connector, path);
	drm_dp_mst_get_port_malloc(port);
	return 0;
}