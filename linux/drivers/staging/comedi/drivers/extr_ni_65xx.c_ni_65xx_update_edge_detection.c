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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int NI_65XX_CHAN_TO_PORT (unsigned int) ; 
 scalar_t__ NI_65XX_FALL_EDGE_ENA_REG (unsigned int) ; 
 unsigned int NI_65XX_PORT_TO_CHAN (unsigned int) ; 
 scalar_t__ NI_65XX_RISE_EDGE_ENA_REG (unsigned int) ; 
 unsigned int ni_65xx_num_ports (struct comedi_device*) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void ni_65xx_update_edge_detection(struct comedi_device *dev,
					  unsigned int base_chan,
					  unsigned int rising,
					  unsigned int falling)
{
	unsigned int num_ports = ni_65xx_num_ports(dev);
	unsigned int port;

	if (base_chan >= NI_65XX_PORT_TO_CHAN(num_ports))
		return;

	for (port = NI_65XX_CHAN_TO_PORT(base_chan); port < num_ports; port++) {
		int bitshift = (int)(NI_65XX_PORT_TO_CHAN(port) - base_chan);
		unsigned int port_mask, port_rising, port_falling;

		if (bitshift >= 32)
			break;

		if (bitshift >= 0) {
			port_mask = ~0U >> bitshift;
			port_rising = rising >> bitshift;
			port_falling = falling >> bitshift;
		} else {
			port_mask = ~0U << -bitshift;
			port_rising = rising << -bitshift;
			port_falling = falling << -bitshift;
		}
		if (port_mask & 0xff) {
			if (~port_mask & 0xff) {
				port_rising |=
				    readb(dev->mmio +
					  NI_65XX_RISE_EDGE_ENA_REG(port)) &
				    ~port_mask;
				port_falling |=
				    readb(dev->mmio +
					  NI_65XX_FALL_EDGE_ENA_REG(port)) &
				    ~port_mask;
			}
			writeb(port_rising & 0xff,
			       dev->mmio + NI_65XX_RISE_EDGE_ENA_REG(port));
			writeb(port_falling & 0xff,
			       dev->mmio + NI_65XX_FALL_EDGE_ENA_REG(port));
		}
	}
}