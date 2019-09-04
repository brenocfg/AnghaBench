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
struct TYPE_2__ {struct drm_encoder* encoder; } ;
struct tc_data {TYPE_1__ bridge; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct tc_data* connector_to_tc (struct drm_connector*) ; 

__attribute__((used)) static struct drm_encoder *
tc_connector_best_encoder(struct drm_connector *connector)
{
	struct tc_data *tc = connector_to_tc(connector);

	return tc->bridge.encoder;
}