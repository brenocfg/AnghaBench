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
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct octeon_device {scalar_t__ num_oqs; scalar_t__ chip; } ;
struct octeon_cn23xx_vf {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int CFG_GET_OQ_INTR_PKT (int /*<<< orphan*/ ) ; 
 scalar_t__ CFG_GET_OQ_INTR_TIME (int /*<<< orphan*/ ) ; 
 int CN23XX_INTR_CINT_ENB ; 
 int CN23XX_INTR_MBOX_ENB ; 
 int CN23XX_PKT_IN_DONE_CNT_MASK ; 
 int /*<<< orphan*/  CN23XX_VF_SLI_IQ_INSTR_COUNT64 (scalar_t__) ; 
 int /*<<< orphan*/  CN23XX_VF_SLI_OQ_PKT_INT_LEVELS (scalar_t__) ; 
 int /*<<< orphan*/  CN23XX_VF_SLI_PKT_MBOX_INT (int /*<<< orphan*/ ) ; 
 int OCTEON_INPUT_INTR ; 
 int OCTEON_MBOX_INTR ; 
 int OCTEON_OUTPUT_INTR ; 
 scalar_t__ cn23xx_vf_get_oq_ticks (struct octeon_device*,scalar_t__) ; 
 int octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cn23xx_enable_vf_interrupt(struct octeon_device *oct, u8 intr_flag)
{
	struct octeon_cn23xx_vf *cn23xx = (struct octeon_cn23xx_vf *)oct->chip;
	u32 q_no, time_threshold;

	if (intr_flag & OCTEON_OUTPUT_INTR) {
		for (q_no = 0; q_no < oct->num_oqs; q_no++) {
			/* Set up interrupt packet and time thresholds
			 * for all the OQs
			 */
			time_threshold = cn23xx_vf_get_oq_ticks(
				oct, (u32)CFG_GET_OQ_INTR_TIME(cn23xx->conf));

			octeon_write_csr64(
			    oct, CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(q_no),
			    (CFG_GET_OQ_INTR_PKT(cn23xx->conf) |
			     ((u64)time_threshold << 32)));
		}
	}

	if (intr_flag & OCTEON_INPUT_INTR) {
		for (q_no = 0; q_no < oct->num_oqs; q_no++) {
			/* Set CINT_ENB to enable IQ interrupt */
			octeon_write_csr64(
			    oct, CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no),
			    ((octeon_read_csr64(
				  oct, CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no)) &
			      ~CN23XX_PKT_IN_DONE_CNT_MASK) |
			     CN23XX_INTR_CINT_ENB));
		}
	}

	/* Set queue-0 MBOX_ENB to enable VF mailbox interrupt */
	if (intr_flag & OCTEON_MBOX_INTR) {
		octeon_write_csr64(
		    oct, CN23XX_VF_SLI_PKT_MBOX_INT(0),
		    (octeon_read_csr64(oct, CN23XX_VF_SLI_PKT_MBOX_INT(0)) |
		     CN23XX_INTR_MBOX_ENB));
	}
}