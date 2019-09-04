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
typedef  int u8 ;
typedef  int u16 ;
typedef  enum fman_port_type { ____Placeholder_fman_port_type } fman_port_type ;

/* Variables and functions */
#define  FMAN_PORT_TYPE_RX 129 
#define  FMAN_PORT_TYPE_TX 128 

__attribute__((used)) static int get_dflt_extra_num_of_open_dmas(u8 major, enum fman_port_type type,
					   u16 speed)
{
	/* FMan V3 */
	if (major >= 6)
		return 0;

	/* FMan V2 */
	switch (type) {
	case FMAN_PORT_TYPE_RX:
	case FMAN_PORT_TYPE_TX:
		if (speed == 10000)
			return 8;
		else
			return 1;
	default:
		return 0;
	}
}