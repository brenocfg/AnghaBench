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
 int /*<<< orphan*/  pcmcia_init_failed ; 
 int /*<<< orphan*/  pcmcia_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_host_pcmcia_driver ; 

void ssb_host_pcmcia_exit(void)
{
	if (!pcmcia_init_failed)
		pcmcia_unregister_driver(&ssb_host_pcmcia_driver);
}