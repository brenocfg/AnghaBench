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
struct beiscsi_hba {int /*<<< orphan*/ * ipv4_iface; int /*<<< orphan*/ * ipv6_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_destroy_iface (int /*<<< orphan*/ *) ; 

void beiscsi_iface_destroy_default(struct beiscsi_hba *phba)
{
	if (phba->ipv6_iface) {
		iscsi_destroy_iface(phba->ipv6_iface);
		phba->ipv6_iface = NULL;
	}
	if (phba->ipv4_iface) {
		iscsi_destroy_iface(phba->ipv4_iface);
		phba->ipv4_iface = NULL;
	}
}