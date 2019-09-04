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
struct ide_host {int host_flags; int /*<<< orphan*/  (* get_lock ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  host_busy; } ;
typedef  int /*<<< orphan*/  ide_hwif_t ;

/* Variables and functions */
 int IDE_HFLAG_SERIALIZE ; 
 int /*<<< orphan*/  IDE_HOST_BUSY ; 
 int /*<<< orphan*/  ide_intr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ide_lock_host(struct ide_host *host, ide_hwif_t *hwif)
{
	int rc = 0;

	if (host->host_flags & IDE_HFLAG_SERIALIZE) {
		rc = test_and_set_bit_lock(IDE_HOST_BUSY, &host->host_busy);
		if (rc == 0) {
			if (host->get_lock)
				host->get_lock(ide_intr, hwif);
		}
	}
	return rc;
}