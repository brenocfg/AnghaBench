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
struct zfcp_dbf {int /*<<< orphan*/  rec; int /*<<< orphan*/  pay; int /*<<< orphan*/  hba; int /*<<< orphan*/  san; int /*<<< orphan*/  scsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct zfcp_dbf*) ; 

__attribute__((used)) static void zfcp_dbf_unregister(struct zfcp_dbf *dbf)
{
	if (!dbf)
		return;

	debug_unregister(dbf->scsi);
	debug_unregister(dbf->san);
	debug_unregister(dbf->hba);
	debug_unregister(dbf->pay);
	debug_unregister(dbf->rec);
	kfree(dbf);
}