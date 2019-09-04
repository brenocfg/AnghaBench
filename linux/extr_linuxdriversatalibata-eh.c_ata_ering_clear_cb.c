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
struct ata_ering_entry {int /*<<< orphan*/  eflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_EFLAG_OLD_ER ; 

__attribute__((used)) static int ata_ering_clear_cb(struct ata_ering_entry *ent, void *void_arg)
{
	ent->eflags |= ATA_EFLAG_OLD_ER;
	return 0;
}