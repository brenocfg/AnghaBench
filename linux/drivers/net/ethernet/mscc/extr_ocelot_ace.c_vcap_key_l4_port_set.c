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
typedef  int /*<<< orphan*/  u32 ;
struct vcap_data {int dummy; } ;
struct ocelot_vcap_udp_tcp {int /*<<< orphan*/  mask; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  vcap_key_set (struct vcap_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vcap_key_l4_port_set(struct vcap_data *data, u32 offset,
				 struct ocelot_vcap_udp_tcp *port)
{
	vcap_key_set(data, offset, 16, port->value, port->mask);
}