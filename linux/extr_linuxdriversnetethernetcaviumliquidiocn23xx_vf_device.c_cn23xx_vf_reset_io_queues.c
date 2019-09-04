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
typedef  scalar_t__ u32 ;
struct octeon_device {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BUSY_READING_REG_VF_LOOP_COUNT ; 
 int CN23XX_PKT_INPUT_CTL_QUIET ; 
 int CN23XX_PKT_INPUT_CTL_RST ; 
 int /*<<< orphan*/  CN23XX_VF_SLI_IQ_PKT_CONTROL64 (scalar_t__) ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cn23xx_vf_reset_io_queues(struct octeon_device *oct, u32 num_queues)
{
	u32 loop = BUSY_READING_REG_VF_LOOP_COUNT;
	int ret_val = 0;
	u32 q_no;
	u64 d64;

	for (q_no = 0; q_no < num_queues; q_no++) {
		/* set RST bit to 1. This bit applies to both IQ and OQ */
		d64 = octeon_read_csr64(oct,
					CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no));
		d64 |= CN23XX_PKT_INPUT_CTL_RST;
		octeon_write_csr64(oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no),
				   d64);
	}

	/* wait until the RST bit is clear or the RST and QUIET bits are set */
	for (q_no = 0; q_no < num_queues; q_no++) {
		u64 reg_val = octeon_read_csr64(oct,
					CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no));
		while ((READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_RST) &&
		       !(READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_QUIET) &&
		       loop) {
			WRITE_ONCE(reg_val, octeon_read_csr64(
			    oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no)));
			loop--;
		}
		if (!loop) {
			dev_err(&oct->pci_dev->dev,
				"clearing the reset reg failed or setting the quiet reg failed for qno: %u\n",
				q_no);
			return -1;
		}
		WRITE_ONCE(reg_val, READ_ONCE(reg_val) &
			   ~CN23XX_PKT_INPUT_CTL_RST);
		octeon_write_csr64(oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no),
				   READ_ONCE(reg_val));

		WRITE_ONCE(reg_val, octeon_read_csr64(
		    oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no)));
		if (READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_RST) {
			dev_err(&oct->pci_dev->dev,
				"clearing the reset failed for qno: %u\n",
				q_no);
			ret_val = -1;
		}
	}

	return ret_val;
}