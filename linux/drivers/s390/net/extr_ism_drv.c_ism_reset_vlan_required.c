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
struct smcd_dev {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_RESET_VLAN ; 
 int ism_cmd_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ism_reset_vlan_required(struct smcd_dev *smcd)
{
	return ism_cmd_simple(smcd->priv, ISM_RESET_VLAN);
}