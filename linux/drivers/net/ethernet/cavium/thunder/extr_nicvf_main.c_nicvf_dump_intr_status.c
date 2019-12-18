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
struct nicvf {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_VF_INT ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_info (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_reg_read (struct nicvf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nicvf_dump_intr_status(struct nicvf *nic)
{
	netif_info(nic, intr, nic->netdev, "interrupt status 0x%llx\n",
		   nicvf_reg_read(nic, NIC_VF_INT));
}