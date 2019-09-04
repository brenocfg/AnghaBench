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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int pf_srn; } ;
struct octeon_device {int num_iqs; TYPE_1__ sriov_info; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int CN23XX_PKT_INPUT_CTL_RING_ENB ; 
 int CN23XX_PKT_INPUT_CTL_RST ; 
 int /*<<< orphan*/  CN23XX_SLI_IQ_DOORBELL (int) ; 
 int /*<<< orphan*/  CN23XX_SLI_IQ_PKT_CONTROL64 (int) ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_PKTS_CREDIT (int) ; 
 int /*<<< orphan*/  CN23XX_SLI_OQ_PKTS_SENT (int) ; 
 int /*<<< orphan*/  CN23XX_SLI_PKT_IOQ_RING_RST ; 
 int HZ ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int octeon_read_csr (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static void cn23xx_disable_io_queues(struct octeon_device *oct)
{
	int q_no, loop;
	u64 d64;
	u32 d32;
	u32 srn, ern;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->num_iqs;

	/*** Disable Input Queues. ***/
	for (q_no = srn; q_no < ern; q_no++) {
		loop = HZ;

		/* start the Reset for a particular ring */
		WRITE_ONCE(d64, octeon_read_csr64(
			   oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no)));
		WRITE_ONCE(d64, READ_ONCE(d64) &
					(~(CN23XX_PKT_INPUT_CTL_RING_ENB)));
		WRITE_ONCE(d64, READ_ONCE(d64) | CN23XX_PKT_INPUT_CTL_RST);
		octeon_write_csr64(oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
				   READ_ONCE(d64));

		/* Wait until hardware indicates that the particular IQ
		 * is out of reset.
		 */
		WRITE_ONCE(d64, octeon_read_csr64(
					oct, CN23XX_SLI_PKT_IOQ_RING_RST));
		while (!(READ_ONCE(d64) & BIT_ULL(q_no)) && loop--) {
			WRITE_ONCE(d64, octeon_read_csr64(
					oct, CN23XX_SLI_PKT_IOQ_RING_RST));
			schedule_timeout_uninterruptible(1);
		}

		/* Reset the doorbell register for this Input Queue. */
		octeon_write_csr(oct, CN23XX_SLI_IQ_DOORBELL(q_no), 0xFFFFFFFF);
		while (octeon_read_csr64(oct, CN23XX_SLI_IQ_DOORBELL(q_no)) &&
		       loop--) {
			schedule_timeout_uninterruptible(1);
		}
	}

	/*** Disable Output Queues. ***/
	for (q_no = srn; q_no < ern; q_no++) {
		loop = HZ;

		/* Wait until hardware indicates that the particular IQ
		 * is out of reset.It given that SLI_PKT_RING_RST is
		 * common for both IQs and OQs
		 */
		WRITE_ONCE(d64, octeon_read_csr64(
					oct, CN23XX_SLI_PKT_IOQ_RING_RST));
		while (!(READ_ONCE(d64) & BIT_ULL(q_no)) && loop--) {
			WRITE_ONCE(d64, octeon_read_csr64(
					oct, CN23XX_SLI_PKT_IOQ_RING_RST));
			schedule_timeout_uninterruptible(1);
		}

		/* Reset the doorbell register for this Output Queue. */
		octeon_write_csr(oct, CN23XX_SLI_OQ_PKTS_CREDIT(q_no),
				 0xFFFFFFFF);
		while (octeon_read_csr64(oct,
					 CN23XX_SLI_OQ_PKTS_CREDIT(q_no)) &&
		       loop--) {
			schedule_timeout_uninterruptible(1);
		}

		/* clear the SLI_PKT(0..63)_CNTS[CNT] reg value */
		WRITE_ONCE(d32, octeon_read_csr(
					oct, CN23XX_SLI_OQ_PKTS_SENT(q_no)));
		octeon_write_csr(oct, CN23XX_SLI_OQ_PKTS_SENT(q_no),
				 READ_ONCE(d32));
	}
}