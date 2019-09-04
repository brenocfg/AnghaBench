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
struct ata_port {struct ahci_port_priv* private_data; } ;
struct ata_link {size_t pmp; int /*<<< orphan*/  flags; struct ata_port* ap; } ;
struct ahci_port_priv {struct ahci_em_priv* em_priv; } ;
struct ahci_em_priv {scalar_t__ blink_policy; int /*<<< orphan*/  timer; struct ata_link* link; scalar_t__ activity; scalar_t__ saved_activity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_LFLAG_SW_ACTIVITY ; 
 int /*<<< orphan*/  ahci_sw_activity_blink ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ahci_init_sw_activity(struct ata_link *link)
{
	struct ata_port *ap = link->ap;
	struct ahci_port_priv *pp = ap->private_data;
	struct ahci_em_priv *emp = &pp->em_priv[link->pmp];

	/* init activity stats, setup timer */
	emp->saved_activity = emp->activity = 0;
	emp->link = link;
	timer_setup(&emp->timer, ahci_sw_activity_blink, 0);

	/* check our blink policy and set flag for link if it's enabled */
	if (emp->blink_policy)
		link->flags |= ATA_LFLAG_SW_ACTIVITY;
}