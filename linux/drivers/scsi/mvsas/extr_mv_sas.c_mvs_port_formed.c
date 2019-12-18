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
struct asd_sas_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvs_port_notify_formed (struct asd_sas_phy*,int) ; 

void mvs_port_formed(struct asd_sas_phy *sas_phy)
{
	mvs_port_notify_formed(sas_phy, 1);
}