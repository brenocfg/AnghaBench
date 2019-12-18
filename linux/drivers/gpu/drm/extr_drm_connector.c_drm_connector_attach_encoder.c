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
struct TYPE_2__ {scalar_t__ id; } ;
struct drm_encoder {TYPE_1__ base; } ;
struct drm_connector {scalar_t__* encoder_ids; int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 

int drm_connector_attach_encoder(struct drm_connector *connector,
				 struct drm_encoder *encoder)
{
	int i;

	/*
	 * In the past, drivers have attempted to model the static association
	 * of connector to encoder in simple connector/encoder devices using a
	 * direct assignment of connector->encoder = encoder. This connection
	 * is a logical one and the responsibility of the core, so drivers are
	 * expected not to mess with this.
	 *
	 * Note that the error return should've been enough here, but a large
	 * majority of drivers ignores the return value, so add in a big WARN
	 * to get people's attention.
	 */
	if (WARN_ON(connector->encoder))
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(connector->encoder_ids); i++) {
		if (connector->encoder_ids[i] == 0) {
			connector->encoder_ids[i] = encoder->base.id;
			return 0;
		}
	}
	return -ENOMEM;
}