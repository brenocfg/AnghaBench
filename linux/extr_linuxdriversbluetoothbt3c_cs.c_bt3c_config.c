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
struct pcmcia_device {struct bt3c_info* priv; } ;
struct bt3c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  bt3c_check_config ; 
 int /*<<< orphan*/  bt3c_check_config_notpicky ; 
 int /*<<< orphan*/  bt3c_interrupt ; 
 scalar_t__ bt3c_open (struct bt3c_info*) ; 
 int /*<<< orphan*/  bt3c_release (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,void*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bt3c_config(struct pcmcia_device *link)
{
	struct bt3c_info *info = link->priv;
	int i;
	unsigned long try;

	/* First pass: look for a config entry that looks normal.
	 * Two tries: without IO aliases, then with aliases
	 */
	for (try = 0; try < 2; try++)
		if (!pcmcia_loop_config(link, bt3c_check_config, (void *) try))
			goto found_port;

	/* Second pass: try to find an entry that isn't picky about
	 * its base address, then try to grab any standard serial port
	 * address, and finally try to get any free port.
	 */
	if (!pcmcia_loop_config(link, bt3c_check_config_notpicky, NULL))
		goto found_port;

	BT_ERR("No usable port range found");
	goto failed;

found_port:
	i = pcmcia_request_irq(link, &bt3c_interrupt);
	if (i != 0)
		goto failed;

	i = pcmcia_enable_device(link);
	if (i != 0)
		goto failed;

	if (bt3c_open(info) != 0)
		goto failed;

	return 0;

failed:
	bt3c_release(link);
	return -ENODEV;
}