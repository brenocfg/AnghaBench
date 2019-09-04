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
struct drm_encoder {scalar_t__ encoder_type; } ;
struct TYPE_2__ {struct drm_encoder base; } ;
struct nouveau_encoder {TYPE_1__ base; } ;
struct drm_connector {scalar_t__ connector_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_OUTPUT_ANY ; 
 scalar_t__ DRM_MODE_CONNECTOR_DisplayPort ; 
 scalar_t__ DRM_MODE_ENCODER_DPMST ; 
 struct nouveau_encoder* find_encoder (struct drm_connector*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
nouveau_connector_is_mst(struct drm_connector *connector)
{
	const struct nouveau_encoder *nv_encoder;
	const struct drm_encoder *encoder;

	if (connector->connector_type != DRM_MODE_CONNECTOR_DisplayPort)
		return false;

	nv_encoder = find_encoder(connector, DCB_OUTPUT_ANY);
	if (!nv_encoder)
		return false;

	encoder = &nv_encoder->base.base;
	return encoder->encoder_type == DRM_MODE_ENCODER_DPMST;
}