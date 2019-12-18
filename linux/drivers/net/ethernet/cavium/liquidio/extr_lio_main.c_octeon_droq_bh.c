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
struct octeon_device_priv {int /*<<< orphan*/  droq_tasklet; } ;
struct TYPE_4__ {int pf_srn; } ;
struct TYPE_3__ {int oq; } ;
struct octeon_device {TYPE_2__ sriov_info; scalar_t__ msix_on; int /*<<< orphan*/ * droq; TYPE_1__ io_qmask; scalar_t__ priv; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_PKTS_SENT (int) ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_PKT_INT_LEVELS (int) ; 
 int MAX_OCTEON_OUTPUT_QUEUES (struct octeon_device*) ; 
 int /*<<< orphan*/  MAX_PACKET_BUDGET ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_enable_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int octeon_droq_process_packets (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void octeon_droq_bh(unsigned long pdev)
{
	int q_no;
	int reschedule = 0;
	struct octeon_device *oct = (struct octeon_device *)pdev;
	struct octeon_device_priv *oct_priv =
		(struct octeon_device_priv *)oct->priv;

	for (q_no = 0; q_no < MAX_OCTEON_OUTPUT_QUEUES(oct); q_no++) {
		if (!(oct->io_qmask.oq & BIT_ULL(q_no)))
			continue;
		reschedule |= octeon_droq_process_packets(oct, oct->droq[q_no],
							  MAX_PACKET_BUDGET);
		lio_enable_irq(oct->droq[q_no], NULL);

		if (OCTEON_CN23XX_PF(oct) && oct->msix_on) {
			/* set time and cnt interrupt thresholds for this DROQ
			 * for NAPI
			 */
			int adjusted_q_no = q_no + oct->sriov_info.pf_srn;

			octeon_write_csr64(
			    oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(adjusted_q_no),
			    0x5700000040ULL);
			octeon_write_csr64(
			    oct, CN23XX_SLI_OQ_PKTS_SENT(adjusted_q_no), 0);
		}
	}

	if (reschedule)
		tasklet_schedule(&oct_priv->droq_tasklet);
}