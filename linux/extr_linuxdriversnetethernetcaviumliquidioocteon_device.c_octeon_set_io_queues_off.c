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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ rings_per_vf; } ;
struct octeon_device {scalar_t__ chip_id; TYPE_2__* pci_dev; TYPE_1__ sriov_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BUSY_READING_REG_VF_LOOP_COUNT ; 
 int CN23XX_PKT_INPUT_CTL_QUIET ; 
 int CN23XX_PKT_INPUT_CTL_RST ; 
 int /*<<< orphan*/  CN23XX_SLI_IQ_PKT_CONTROL64 (scalar_t__) ; 
 int /*<<< orphan*/  CN23XX_VF_SLI_IQ_PKT_CONTROL64 (scalar_t__) ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_INSTR_ENB ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_OUT_ENB ; 
 scalar_t__ OCTEON_CN23XX_VF_VID ; 
 scalar_t__ OCTEON_CN6XXX (struct octeon_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

int octeon_set_io_queues_off(struct octeon_device *oct)
{
	int loop = BUSY_READING_REG_VF_LOOP_COUNT;

	if (OCTEON_CN6XXX(oct)) {
		octeon_write_csr(oct, CN6XXX_SLI_PKT_INSTR_ENB, 0);
		octeon_write_csr(oct, CN6XXX_SLI_PKT_OUT_ENB, 0);
	} else if (oct->chip_id == OCTEON_CN23XX_VF_VID) {
		u32 q_no;

		/* IOQs will already be in reset.
		 * If RST bit is set, wait for quiet bit to be set.
		 * Once quiet bit is set, clear the RST bit.
		 */
		for (q_no = 0; q_no < oct->sriov_info.rings_per_vf; q_no++) {
			u64 reg_val = octeon_read_csr64(
				oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no));

			while ((reg_val & CN23XX_PKT_INPUT_CTL_RST) &&
			       !(reg_val &  CN23XX_PKT_INPUT_CTL_QUIET) &&
			       loop) {
				reg_val = octeon_read_csr64(
					oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
				loop--;
			}
			if (!loop) {
				dev_err(&oct->pci_dev->dev,
					"clearing the reset reg failed or setting the quiet reg failed for qno: %u\n",
					q_no);
				return -1;
			}

			reg_val = reg_val & ~CN23XX_PKT_INPUT_CTL_RST;
			octeon_write_csr64(oct,
					   CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
					   reg_val);

			reg_val = octeon_read_csr64(
					oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
			if (reg_val & CN23XX_PKT_INPUT_CTL_RST) {
				dev_err(&oct->pci_dev->dev,
					"unable to reset qno %u\n", q_no);
				return -1;
			}
		}
	}
	return 0;
}