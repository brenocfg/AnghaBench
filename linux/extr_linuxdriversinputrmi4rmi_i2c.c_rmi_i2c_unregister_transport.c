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
struct rmi_i2c_xport {int /*<<< orphan*/  xport; } ;

/* Variables and functions */
 int /*<<< orphan*/  rmi_unregister_transport_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rmi_i2c_unregister_transport(void *data)
{
	struct rmi_i2c_xport *rmi_i2c = data;

	rmi_unregister_transport_device(&rmi_i2c->xport);
}