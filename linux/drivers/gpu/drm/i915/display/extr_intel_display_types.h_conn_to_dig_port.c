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
struct intel_digital_port {int dummy; } ;
struct intel_connector {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 TYPE_1__* intel_attached_encoder (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct intel_digital_port *
conn_to_dig_port(struct intel_connector *connector)
{
	return enc_to_dig_port(&intel_attached_encoder(&connector->base)->base);
}