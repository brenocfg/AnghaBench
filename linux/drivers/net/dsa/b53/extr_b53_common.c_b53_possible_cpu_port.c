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
struct dsa_switch {int dummy; } ;

/* Variables and functions */
#define  B53_CPU_PORT 129 
#define  B53_CPU_PORT_25 128 

__attribute__((used)) static bool b53_possible_cpu_port(struct dsa_switch *ds, int port)
{
	/* Broadcom switches will accept enabling Broadcom tags on the
	 * following ports: 5, 7 and 8, any other port is not supported
	 */
	switch (port) {
	case B53_CPU_PORT_25:
	case 7:
	case B53_CPU_PORT:
		return true;
	}

	return false;
}