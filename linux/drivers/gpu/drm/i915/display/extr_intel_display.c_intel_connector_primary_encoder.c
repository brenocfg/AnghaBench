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
struct intel_encoder {int dummy; } ;
struct intel_connector {int /*<<< orphan*/  base; scalar_t__ mst_port; } ;
struct TYPE_2__ {struct intel_encoder base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* dp_to_dig_port (scalar_t__) ; 
 struct intel_encoder* intel_attached_encoder (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct intel_encoder *
intel_connector_primary_encoder(struct intel_connector *connector)
{
	struct intel_encoder *encoder;

	if (connector->mst_port)
		return &dp_to_dig_port(connector->mst_port)->base;

	encoder = intel_attached_encoder(&connector->base);
	WARN_ON(!encoder);

	return encoder;
}