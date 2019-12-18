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
struct parport {int dummy; } ;

/* Variables and functions */
#define  IEEE1284_MODE_BECP 137 
#define  IEEE1284_MODE_BYTE 136 
#define  IEEE1284_MODE_COMPAT 135 
#define  IEEE1284_MODE_ECP 134 
#define  IEEE1284_MODE_ECPRLE 133 
#define  IEEE1284_MODE_ECPSWE 132 
#define  IEEE1284_MODE_EPP 131 
#define  IEEE1284_MODE_EPPSL 130 
#define  IEEE1284_MODE_EPPSWE 129 
#define  IEEE1284_MODE_NIBBLE 128 
 int PARPORT_STATUS_ERROR ; 
 int cpp_daisy (struct parport*,int) ; 

int parport_daisy_select(struct parport *port, int daisy, int mode)
{
	switch (mode)
	{
		// For these modes we should switch to EPP mode:
		case IEEE1284_MODE_EPP:
		case IEEE1284_MODE_EPPSL:
		case IEEE1284_MODE_EPPSWE:
			return !(cpp_daisy(port, 0x20 + daisy) &
				 PARPORT_STATUS_ERROR);

		// For these modes we should switch to ECP mode:
		case IEEE1284_MODE_ECP:
		case IEEE1284_MODE_ECPRLE:
		case IEEE1284_MODE_ECPSWE: 
			return !(cpp_daisy(port, 0xd0 + daisy) &
				 PARPORT_STATUS_ERROR);

		// Nothing was told for BECP in Daisy chain specification.
		// May be it's wise to use ECP?
		case IEEE1284_MODE_BECP:
		// Others use compat mode
		case IEEE1284_MODE_NIBBLE:
		case IEEE1284_MODE_BYTE:
		case IEEE1284_MODE_COMPAT:
		default:
			return !(cpp_daisy(port, 0xe0 + daisy) &
				 PARPORT_STATUS_ERROR);
	}
}