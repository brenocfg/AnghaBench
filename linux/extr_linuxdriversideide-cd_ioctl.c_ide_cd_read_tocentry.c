#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  second; int /*<<< orphan*/  minute; } ;
struct TYPE_5__ {int /*<<< orphan*/  lba; TYPE_1__ msf; } ;
struct cdrom_tocentry {scalar_t__ cdte_format; TYPE_2__ cdte_addr; int /*<<< orphan*/  cdte_adr; int /*<<< orphan*/  cdte_ctrl; int /*<<< orphan*/  cdte_track; } ;
struct TYPE_6__ {int /*<<< orphan*/  lba; } ;
struct atapi_toc_entry {TYPE_3__ addr; int /*<<< orphan*/  adr; int /*<<< orphan*/  control; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 scalar_t__ CDROM_MSF ; 
 int ide_cd_get_toc_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct atapi_toc_entry**) ; 
 int /*<<< orphan*/  lba_to_msf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ide_cd_read_tocentry(ide_drive_t *drive, void *arg)
{
	struct cdrom_tocentry *tocentry = arg;
	struct atapi_toc_entry *toce;
	int stat;

	stat = ide_cd_get_toc_entry(drive, tocentry->cdte_track, &toce);
	if (stat)
		return stat;

	tocentry->cdte_ctrl = toce->control;
	tocentry->cdte_adr  = toce->adr;
	if (tocentry->cdte_format == CDROM_MSF) {
		lba_to_msf(toce->addr.lba,
			   &tocentry->cdte_addr.msf.minute,
			   &tocentry->cdte_addr.msf.second,
			   &tocentry->cdte_addr.msf.frame);
	} else
		tocentry->cdte_addr.lba = toce->addr.lba;

	return 0;
}