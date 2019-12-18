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
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_2__ {int (* detect ) (struct drm_encoder*,struct drm_connector*) ;} ;

/* Variables and functions */
 TYPE_1__* get_slave_funcs (struct drm_encoder*) ; 
 int stub1 (struct drm_encoder*,struct drm_connector*) ; 

enum drm_connector_status drm_i2c_encoder_detect(struct drm_encoder *encoder,
	    struct drm_connector *connector)
{
	return get_slave_funcs(encoder)->detect(encoder, connector);
}