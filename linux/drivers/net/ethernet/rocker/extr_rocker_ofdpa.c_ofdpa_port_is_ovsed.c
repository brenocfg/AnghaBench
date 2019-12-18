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
struct ofdpa_port {int dummy; } ;

/* Variables and functions */
 int ofdpa_port_is_slave (struct ofdpa_port const*,char*) ; 

__attribute__((used)) static bool ofdpa_port_is_ovsed(const struct ofdpa_port *ofdpa_port)
{
	return ofdpa_port_is_slave(ofdpa_port, "openvswitch");
}