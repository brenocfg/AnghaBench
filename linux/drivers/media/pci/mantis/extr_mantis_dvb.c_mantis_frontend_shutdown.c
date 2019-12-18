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
struct mantis_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  POWER_OFF ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int mantis_frontend_power (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mantis_frontend_soft_reset (struct mantis_pci*) ; 

__attribute__((used)) static int mantis_frontend_shutdown(struct mantis_pci *mantis)
{
	int err;

	mantis_frontend_soft_reset(mantis);
	err = mantis_frontend_power(mantis, POWER_OFF);
	if (err != 0) {
		dprintk(MANTIS_ERROR, 1, "Frontend POWER OFF failed! <%d>", err);
		return 1;
	}

	return 0;
}