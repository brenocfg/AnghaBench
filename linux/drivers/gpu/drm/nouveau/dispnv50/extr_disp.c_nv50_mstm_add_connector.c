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
struct nv50_mstm {int dummy; } ;
struct drm_connector {int dummy; } ;
struct nv50_mstc {struct drm_connector connector; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {int dummy; } ;

/* Variables and functions */
 int nv50_mstc_new (struct nv50_mstm*,struct drm_dp_mst_port*,char const*,struct nv50_mstc**) ; 
 struct nv50_mstm* nv50_mstm (struct drm_dp_mst_topology_mgr*) ; 

__attribute__((used)) static struct drm_connector *
nv50_mstm_add_connector(struct drm_dp_mst_topology_mgr *mgr,
			struct drm_dp_mst_port *port, const char *path)
{
	struct nv50_mstm *mstm = nv50_mstm(mgr);
	struct nv50_mstc *mstc;
	int ret;

	ret = nv50_mstc_new(mstm, port, path, &mstc);
	if (ret)
		return NULL;

	return &mstc->connector;
}