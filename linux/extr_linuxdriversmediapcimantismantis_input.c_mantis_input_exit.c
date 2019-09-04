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
struct mantis_pci {int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 

void mantis_input_exit(struct mantis_pci *mantis)
{
	rc_unregister_device(mantis->rc);
}