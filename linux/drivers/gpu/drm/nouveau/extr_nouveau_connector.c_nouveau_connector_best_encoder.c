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
struct nouveau_connector {scalar_t__ detected_encoder; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct nouveau_connector* nouveau_connector (struct drm_connector*) ; 
 struct drm_encoder* to_drm_encoder (scalar_t__) ; 

__attribute__((used)) static struct drm_encoder *
nouveau_connector_best_encoder(struct drm_connector *connector)
{
	struct nouveau_connector *nv_connector = nouveau_connector(connector);

	if (nv_connector->detected_encoder)
		return to_drm_encoder(nv_connector->detected_encoder);

	return NULL;
}