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
struct ksz_device {int features; } ;

/* Variables and functions */
 int GBIT_SUPPORT ; 
 int /*<<< orphan*/  ksz9477_port_mmd_write (struct ksz_device*,int,int,int,int) ; 

__attribute__((used)) static void ksz9477_phy_errata_setup(struct ksz_device *dev, int port)
{
	/* Apply PHY settings to address errata listed in
	 * KSZ9477, KSZ9897, KSZ9896, KSZ9567, KSZ8565
	 * Silicon Errata and Data Sheet Clarification documents:
	 *
	 * Register settings are needed to improve PHY receive performance
	 */
	ksz9477_port_mmd_write(dev, port, 0x01, 0x6f, 0xdd0b);
	ksz9477_port_mmd_write(dev, port, 0x01, 0x8f, 0x6032);
	ksz9477_port_mmd_write(dev, port, 0x01, 0x9d, 0x248c);
	ksz9477_port_mmd_write(dev, port, 0x01, 0x75, 0x0060);
	ksz9477_port_mmd_write(dev, port, 0x01, 0xd3, 0x7777);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x06, 0x3008);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x08, 0x2001);

	/* Transmit waveform amplitude can be improved
	 * (1000BASE-T, 100BASE-TX, 10BASE-Te)
	 */
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x04, 0x00d0);

	/* Energy Efficient Ethernet (EEE) feature select must
	 * be manually disabled (except on KSZ8565 which is 100Mbit)
	 */
	if (dev->features & GBIT_SUPPORT)
		ksz9477_port_mmd_write(dev, port, 0x07, 0x3c, 0x0000);

	/* Register settings are required to meet data sheet
	 * supply current specifications
	 */
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x13, 0x6eff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x14, 0xe6ff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x15, 0x6eff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x16, 0xe6ff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x17, 0x00ff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x18, 0x43ff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x19, 0xc3ff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x1a, 0x6fff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x1b, 0x07ff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x1c, 0x0fff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x1d, 0xe7ff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x1e, 0xefff);
	ksz9477_port_mmd_write(dev, port, 0x1c, 0x20, 0xeeee);
}