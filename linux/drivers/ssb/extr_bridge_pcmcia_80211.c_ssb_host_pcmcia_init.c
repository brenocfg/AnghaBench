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
 int pcmcia_init_failed ; 
 int pcmcia_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_host_pcmcia_driver ; 

int ssb_host_pcmcia_init(void)
{
	pcmcia_init_failed = pcmcia_register_driver(&ssb_host_pcmcia_driver);

	return pcmcia_init_failed;
}