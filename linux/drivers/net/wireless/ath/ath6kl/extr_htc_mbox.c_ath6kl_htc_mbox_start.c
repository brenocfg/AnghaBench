#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct htc_target {TYPE_1__* dev; int /*<<< orphan*/  tgt_creds; int /*<<< orphan*/  cred_dist_list; int /*<<< orphan*/  credit_info; scalar_t__ rx_st_flags; scalar_t__ htc_flags; } ;
struct htc_packet {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq_proc_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_credit_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_hif_disable_intrs (TYPE_1__*) ; 
 int ath6kl_hif_unmask_intrs (TYPE_1__*) ; 
 int /*<<< orphan*/  ath6kl_htc_mbox_stop (struct htc_target*) ; 
 int /*<<< orphan*/  dump_cred_dist_stats (struct htc_target*) ; 
 int htc_add_rxbuf (struct htc_target*,struct htc_packet*) ; 
 struct htc_packet* htc_get_control_buf (struct htc_target*,int) ; 
 int htc_setup_tx_complete (struct htc_target*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath6kl_htc_mbox_start(struct htc_target *target)
{
	struct htc_packet *packet;
	int status;

	memset(&target->dev->irq_proc_reg, 0,
	       sizeof(target->dev->irq_proc_reg));

	/* Disable interrupts at the chip level */
	ath6kl_hif_disable_intrs(target->dev);

	target->htc_flags = 0;
	target->rx_st_flags = 0;

	/* Push control receive buffers into htc control endpoint */
	while ((packet = htc_get_control_buf(target, false)) != NULL) {
		status = htc_add_rxbuf(target, packet);
		if (status)
			return status;
	}

	/* NOTE: the first entry in the distribution list is ENDPOINT_0 */
	ath6kl_credit_init(target->credit_info, &target->cred_dist_list,
			   target->tgt_creds);

	dump_cred_dist_stats(target);

	/* Indicate to the target of the setup completion */
	status = htc_setup_tx_complete(target);

	if (status)
		return status;

	/* unmask interrupts */
	status = ath6kl_hif_unmask_intrs(target->dev);

	if (status)
		ath6kl_htc_mbox_stop(target);

	return status;
}