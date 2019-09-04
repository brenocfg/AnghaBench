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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_connector {int /*<<< orphan*/  base; struct intel_encoder* encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_attach_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void intel_connector_attach_encoder(struct intel_connector *connector,
				    struct intel_encoder *encoder)
{
	connector->encoder = encoder;
	drm_connector_attach_encoder(&connector->base, &encoder->base);
}