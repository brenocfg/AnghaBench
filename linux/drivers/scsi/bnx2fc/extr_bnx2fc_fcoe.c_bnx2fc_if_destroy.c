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
struct fc_lport {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2fc_clean_rx_queue (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_exch_mgr_free (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_free_stats (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2fc_if_destroy(struct fc_lport *lport)
{

	/* Free queued packets for the receive thread */
	bnx2fc_clean_rx_queue(lport);

	/* Detach from scsi-ml */
	fc_remove_host(lport->host);
	scsi_remove_host(lport->host);

	/*
	 * Note that only the physical lport will have the exchange manager.
	 * for vports, this function is NOP
	 */
	fc_exch_mgr_free(lport);

	/* Free memory used by statistical counters */
	fc_lport_free_stats(lport);

	/* Release Scsi_Host */
	scsi_host_put(lport->host);
}