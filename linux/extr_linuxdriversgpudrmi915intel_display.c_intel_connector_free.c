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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct intel_connector {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct intel_connector*) ; 
 struct intel_connector* to_intel_digital_connector_state (int /*<<< orphan*/ ) ; 

void intel_connector_free(struct intel_connector *connector)
{
	kfree(to_intel_digital_connector_state(connector->base.state));
	kfree(connector);
}