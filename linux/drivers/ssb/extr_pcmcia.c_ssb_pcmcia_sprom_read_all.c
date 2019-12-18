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
typedef  int /*<<< orphan*/  u16 ;
struct ssb_bus {int dummy; } ;

/* Variables and functions */
 int SSB_PCMCIA_SPROM_SIZE ; 
 int ssb_pcmcia_sprom_read (struct ssb_bus*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssb_pcmcia_sprom_read_all(struct ssb_bus *bus, u16 *sprom)
{
	int err, i;

	for (i = 0; i < SSB_PCMCIA_SPROM_SIZE; i++) {
		err = ssb_pcmcia_sprom_read(bus, i, &sprom[i]);
		if (err)
			return err;
	}

	return 0;
}