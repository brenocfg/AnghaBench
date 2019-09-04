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

/* Variables and functions */

__attribute__((used)) static unsigned int pdc_port_no_to_ata_no(unsigned int port_no,
					  int is_sataii_tx4)
{
	static const unsigned char sataii_tx4_port_remap[4] = { 3, 1, 0, 2};
	return is_sataii_tx4 ? sataii_tx4_port_remap[port_no] : port_no;
}