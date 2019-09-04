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
struct uart_port {int mapbase; } ;

/* Variables and functions */
 unsigned int CRTSCTS ; 
 int /*<<< orphan*/  PORT_PTCR ; 
 int /*<<< orphan*/  PORT_PVCR ; 
 unsigned short __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh7720_sci_init_pins(struct uart_port *port, unsigned int cflag)
{
	unsigned short data;

	if (cflag & CRTSCTS) {
		/* enable RTS/CTS */
		if (port->mapbase == 0xa4430000) { /* SCIF0 */
			/* Clear PTCR bit 9-2; enable all scif pins but sck */
			data = __raw_readw(PORT_PTCR);
			__raw_writew((data & 0xfc03), PORT_PTCR);
		} else if (port->mapbase == 0xa4438000) { /* SCIF1 */
			/* Clear PVCR bit 9-2 */
			data = __raw_readw(PORT_PVCR);
			__raw_writew((data & 0xfc03), PORT_PVCR);
		}
	} else {
		if (port->mapbase == 0xa4430000) { /* SCIF0 */
			/* Clear PTCR bit 5-2; enable only tx and rx  */
			data = __raw_readw(PORT_PTCR);
			__raw_writew((data & 0xffc3), PORT_PTCR);
		} else if (port->mapbase == 0xa4438000) { /* SCIF1 */
			/* Clear PVCR bit 5-2 */
			data = __raw_readw(PORT_PVCR);
			__raw_writew((data & 0xffc3), PORT_PVCR);
		}
	}
}