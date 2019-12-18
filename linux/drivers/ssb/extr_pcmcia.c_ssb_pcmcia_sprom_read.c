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
struct ssb_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_PCMCIA_SPROMCTL_READ ; 
 int /*<<< orphan*/  SSB_PCMCIA_SPROM_ADDRHI ; 
 int /*<<< orphan*/  SSB_PCMCIA_SPROM_ADDRLO ; 
 int /*<<< orphan*/  SSB_PCMCIA_SPROM_DATAHI ; 
 int /*<<< orphan*/  SSB_PCMCIA_SPROM_DATALO ; 
 int ssb_pcmcia_cfg_read (struct ssb_bus*,int /*<<< orphan*/ ,int*) ; 
 int ssb_pcmcia_cfg_write (struct ssb_bus*,int /*<<< orphan*/ ,int) ; 
 int ssb_pcmcia_sprom_command (struct ssb_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssb_pcmcia_sprom_read(struct ssb_bus *bus, u16 offset, u16 *value)
{
	int err;
	u8 lo, hi;

	offset *= 2; /* Make byte offset */

	err = ssb_pcmcia_cfg_write(bus, SSB_PCMCIA_SPROM_ADDRLO,
				   (offset & 0x00FF));
	if (err)
		return err;
	err = ssb_pcmcia_cfg_write(bus, SSB_PCMCIA_SPROM_ADDRHI,
				   (offset & 0xFF00) >> 8);
	if (err)
		return err;
	err = ssb_pcmcia_sprom_command(bus, SSB_PCMCIA_SPROMCTL_READ);
	if (err)
		return err;
	err = ssb_pcmcia_cfg_read(bus, SSB_PCMCIA_SPROM_DATALO, &lo);
	if (err)
		return err;
	err = ssb_pcmcia_cfg_read(bus, SSB_PCMCIA_SPROM_DATAHI, &hi);
	if (err)
		return err;
	*value = (lo | (((u16)hi) << 8));

	return 0;
}