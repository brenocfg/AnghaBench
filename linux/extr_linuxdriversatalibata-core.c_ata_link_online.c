#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ata_link {TYPE_1__* ap; } ;
struct TYPE_2__ {struct ata_link* slave_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ ata_phys_link_online (struct ata_link*) ; 

bool ata_link_online(struct ata_link *link)
{
	struct ata_link *slave = link->ap->slave_link;

	WARN_ON(link == slave);	/* shouldn't be called on slave link */

	return ata_phys_link_online(link) ||
		(slave && ata_phys_link_online(slave));
}