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
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 

__attribute__((used)) static int mpi_get_phy_profile_resp(struct pm8001_hba_info *pm8001_ha,
			void *piomb)
{
	PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(" pm80xx_addition_functionality\n"));

	return 0;
}