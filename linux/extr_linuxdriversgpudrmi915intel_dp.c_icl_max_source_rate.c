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
struct intel_dp {int dummy; } ;
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int PORT_B ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 

__attribute__((used)) static int icl_max_source_rate(struct intel_dp *intel_dp)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	enum port port = dig_port->base.port;

	if (port == PORT_B)
		return 540000;

	return 810000;
}