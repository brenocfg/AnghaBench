#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* dev; } ;
struct s_smc {TYPE_1__ os; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  STI_FBI () ; 
 int /*<<< orphan*/  card_stop (struct s_smc*) ; 
 int /*<<< orphan*/  init_smt (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_drv_clear_rx_queue (struct s_smc*) ; 
 int /*<<< orphan*/  mac_drv_clear_tx_queue (struct s_smc*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  skfp_ctl_set_multicast_list_wo_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  smt_online (struct s_smc*,int) ; 
 int /*<<< orphan*/  smt_reset_defaults (struct s_smc*,int) ; 

__attribute__((used)) static void ResetAdapter(struct s_smc *smc)
{

	pr_debug("[fddi: ResetAdapter]\n");

	// Stop the adapter.

	card_stop(smc);		// Stop all activity.

	// Clear the transmit and receive descriptor queues.
	mac_drv_clear_tx_queue(smc);
	mac_drv_clear_rx_queue(smc);

	// Restart the adapter.

	smt_reset_defaults(smc, 1);	// Initialize the SMT module.

	init_smt(smc, (smc->os.dev)->dev_addr);	// Initialize the hardware.

	smt_online(smc, 1);	// Insert into the ring again.
	STI_FBI();

	// Restore original receive mode (multicasts, promiscuous, etc.).
	skfp_ctl_set_multicast_list_wo_lock(smc->os.dev);
}