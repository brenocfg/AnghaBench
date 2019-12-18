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
struct nv50_mstc {int /*<<< orphan*/  port; int /*<<< orphan*/  connector; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_mst_put_port_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nv50_mstc*) ; 
 struct nv50_mstc* nv50_mstc (struct drm_connector*) ; 

__attribute__((used)) static void
nv50_mstc_destroy(struct drm_connector *connector)
{
	struct nv50_mstc *mstc = nv50_mstc(connector);

	drm_connector_cleanup(&mstc->connector);
	drm_dp_mst_put_port_malloc(mstc->port);

	kfree(mstc);
}