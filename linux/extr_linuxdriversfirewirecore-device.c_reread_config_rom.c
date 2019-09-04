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
typedef  scalar_t__ u32 ;
struct fw_device {scalar_t__* config_rom; } ;

/* Variables and functions */
 int RCODE_BUSY ; 
 int RCODE_COMPLETE ; 
 int read_rom (struct fw_device*,int,int,scalar_t__*) ; 

__attribute__((used)) static int reread_config_rom(struct fw_device *device, int generation,
			     bool *changed)
{
	u32 q;
	int i, rcode;

	for (i = 0; i < 6; i++) {
		rcode = read_rom(device, generation, i, &q);
		if (rcode != RCODE_COMPLETE)
			return rcode;

		if (i == 0 && q == 0)
			/* inaccessible (see read_config_rom); retry later */
			return RCODE_BUSY;

		if (q != device->config_rom[i]) {
			*changed = true;
			return RCODE_COMPLETE;
		}
	}

	*changed = false;
	return RCODE_COMPLETE;
}