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
struct rpi_power_domain_packet {int on; int /*<<< orphan*/  domain; } ;
struct rpi_power_domain {scalar_t__ old_interface; int /*<<< orphan*/  fw; int /*<<< orphan*/  domain; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int /*<<< orphan*/  RPI_FIRMWARE_SET_DOMAIN_STATE ; 
 int /*<<< orphan*/  RPI_FIRMWARE_SET_POWER_STATE ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpi_power_domain_packet*,int) ; 

__attribute__((used)) static int rpi_firmware_set_power(struct rpi_power_domain *rpi_domain, bool on)
{
	struct rpi_power_domain_packet packet;

	packet.domain = rpi_domain->domain;
	packet.on = on;
	return rpi_firmware_property(rpi_domain->fw,
				     rpi_domain->old_interface ?
				     RPI_FIRMWARE_SET_POWER_STATE :
				     RPI_FIRMWARE_SET_DOMAIN_STATE,
				     &packet, sizeof(packet));
}