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
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
#define  PORT_A 136 
#define  PORT_B 135 
#define  PORT_C 134 
#define  PORT_D 133 
#define  PORT_E 132 
#define  PORT_F 131 
#define  PORT_G 130 
#define  PORT_H 129 
#define  PORT_I 128 

__attribute__((used)) static inline const char *port_identifier(enum port port)
{
	switch (port) {
	case PORT_A:
		return "Port A";
	case PORT_B:
		return "Port B";
	case PORT_C:
		return "Port C";
	case PORT_D:
		return "Port D";
	case PORT_E:
		return "Port E";
	case PORT_F:
		return "Port F";
	case PORT_G:
		return "Port G";
	case PORT_H:
		return "Port H";
	case PORT_I:
		return "Port I";
	default:
		return "<invalid>";
	}
}