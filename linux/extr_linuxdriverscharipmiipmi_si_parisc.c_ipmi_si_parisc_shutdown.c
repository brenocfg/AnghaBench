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
 int /*<<< orphan*/  ipmi_parisc_driver ; 
 scalar_t__ parisc_registered ; 
 int /*<<< orphan*/  unregister_parisc_driver (int /*<<< orphan*/ *) ; 

void ipmi_si_parisc_shutdown(void)
{
	if (parisc_registered)
		unregister_parisc_driver(&ipmi_parisc_driver);
}