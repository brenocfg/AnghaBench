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
struct stm32_dcmi {int /*<<< orphan*/  regs; int /*<<< orphan*/  errors_count; } ;
struct dcmi_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CAPTURE ; 
 int /*<<< orphan*/  DCMI_CR ; 
 int EINVAL ; 
 int dcmi_start_dma (struct stm32_dcmi*,struct dcmi_buf*) ; 
 int /*<<< orphan*/  reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcmi_start_capture(struct stm32_dcmi *dcmi, struct dcmi_buf *buf)
{
	int ret;

	if (!buf)
		return -EINVAL;

	ret = dcmi_start_dma(dcmi, buf);
	if (ret) {
		dcmi->errors_count++;
		return ret;
	}

	/* Enable capture */
	reg_set(dcmi->regs, DCMI_CR, CR_CAPTURE);

	return 0;
}