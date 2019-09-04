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
struct rmi_spi_xport {int /*<<< orphan*/  xport; } ;

/* Variables and functions */
 int /*<<< orphan*/  rmi_unregister_transport_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rmi_spi_unregister_transport(void *data)
{
	struct rmi_spi_xport *rmi_spi = data;

	rmi_unregister_transport_device(&rmi_spi->xport);
}