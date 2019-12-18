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
struct ssb_bus {int mapped_pcmcia_seg; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SSB_BAR0_MAX_RETRIES ; 
 int /*<<< orphan*/  SSB_PCMCIA_MEMSEG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int ssb_pcmcia_cfg_read (struct ssb_bus*,int /*<<< orphan*/ ,int*) ; 
 int ssb_pcmcia_cfg_write (struct ssb_bus*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

int ssb_pcmcia_switch_segment(struct ssb_bus *bus, u8 seg)
{
	int attempts = 0;
	int err;
	u8 val;

	WARN_ON((seg != 0) && (seg != 1));
	while (1) {
		err = ssb_pcmcia_cfg_write(bus, SSB_PCMCIA_MEMSEG, seg);
		if (err)
			goto error;
		err = ssb_pcmcia_cfg_read(bus, SSB_PCMCIA_MEMSEG, &val);
		if (err)
			goto error;
		if (val == seg)
			break;

		err = -ETIMEDOUT;
		if (unlikely(attempts++ > SSB_BAR0_MAX_RETRIES))
			goto error;
		udelay(10);
	}
	bus->mapped_pcmcia_seg = seg;

	return 0;
error:
	pr_err("Failed to switch pcmcia segment\n");
	return err;
}