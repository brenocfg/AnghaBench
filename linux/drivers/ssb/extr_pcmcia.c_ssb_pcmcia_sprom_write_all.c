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
 int EBUSY ; 
 int /*<<< orphan*/  SSB_PCMCIA_SPROMCTL_WRITEDIS ; 
 int /*<<< orphan*/  SSB_PCMCIA_SPROMCTL_WRITEEN ; 
 size_t SSB_PCMCIA_SPROM_SIZE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int ssb_pcmcia_sprom_command (struct ssb_bus*,int /*<<< orphan*/ ) ; 
 int ssb_pcmcia_sprom_write (struct ssb_bus*,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int ssb_pcmcia_sprom_write_all(struct ssb_bus *bus, const u16 *sprom)
{
	int i, err;
	bool failed = 0;
	size_t size = SSB_PCMCIA_SPROM_SIZE;

	pr_notice("Writing SPROM. Do NOT turn off the power! Please stand by...\n");
	err = ssb_pcmcia_sprom_command(bus, SSB_PCMCIA_SPROMCTL_WRITEEN);
	if (err) {
		pr_notice("Could not enable SPROM write access\n");
		return -EBUSY;
	}
	pr_notice("[ 0%%");
	msleep(500);
	for (i = 0; i < size; i++) {
		if (i == size / 4)
			pr_cont("25%%");
		else if (i == size / 2)
			pr_cont("50%%");
		else if (i == (size * 3) / 4)
			pr_cont("75%%");
		else if (i % 2)
			pr_cont(".");
		err = ssb_pcmcia_sprom_write(bus, i, sprom[i]);
		if (err) {
			pr_notice("Failed to write to SPROM\n");
			failed = 1;
			break;
		}
	}
	err = ssb_pcmcia_sprom_command(bus, SSB_PCMCIA_SPROMCTL_WRITEDIS);
	if (err) {
		pr_notice("Could not disable SPROM write access\n");
		failed = 1;
	}
	msleep(500);
	if (!failed) {
		pr_cont("100%% ]\n");
		pr_notice("SPROM written\n");
	}

	return failed ? -EBUSY : 0;
}