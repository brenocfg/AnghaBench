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
struct pcmcia_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EXTRA ; 
 int /*<<< orphan*/  DEBUG_HW ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info ; 
 int prism2_config (struct pcmcia_device*) ; 

__attribute__((used)) static int hostap_cs_probe(struct pcmcia_device *p_dev)
{
	int ret;

	PDEBUG(DEBUG_HW, "%s: setting Vcc=33 (constant)\n", dev_info);

	ret = prism2_config(p_dev);
	if (ret) {
		PDEBUG(DEBUG_EXTRA, "prism2_config() failed\n");
	}

	return ret;
}