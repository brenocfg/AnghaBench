#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  prepare_link_retrain; int /*<<< orphan*/  output_reg; } ;
struct TYPE_3__ {int port; } ;
struct intel_digital_port {TYPE_2__ dp; TYPE_1__ base; } ;
struct intel_connector {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_BUF_CTL (int) ; 
 struct intel_connector* intel_connector_alloc () ; 
 int /*<<< orphan*/  intel_ddi_prepare_link_retrain ; 
 int /*<<< orphan*/  intel_dp_init_connector (struct intel_digital_port*,struct intel_connector*) ; 
 int /*<<< orphan*/  kfree (struct intel_connector*) ; 

__attribute__((used)) static struct intel_connector *
intel_ddi_init_dp_connector(struct intel_digital_port *intel_dig_port)
{
	struct intel_connector *connector;
	enum port port = intel_dig_port->base.port;

	connector = intel_connector_alloc();
	if (!connector)
		return NULL;

	intel_dig_port->dp.output_reg = DDI_BUF_CTL(port);
	intel_dig_port->dp.prepare_link_retrain =
		intel_ddi_prepare_link_retrain;

	if (!intel_dp_init_connector(intel_dig_port, connector)) {
		kfree(connector);
		return NULL;
	}

	return connector;
}