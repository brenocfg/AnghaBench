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
typedef  int u32 ;
struct hisi_sas_hw_error {int irq_msk; int msk; int shift; int /*<<< orphan*/  msg; int /*<<< orphan*/  reg; } ;
struct hisi_hba {int /*<<< orphan*/  rst_work; int /*<<< orphan*/  wq; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hisi_sas_hw_error*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int,int) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 struct hisi_sas_hw_error* multi_bit_ecc_errors ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void multi_bit_ecc_error_process_v2_hw(struct hisi_hba *hisi_hba,
		u32 irq_value)
{
	struct device *dev = hisi_hba->dev;
	const struct hisi_sas_hw_error *ecc_error;
	u32 val;
	int i;

	for (i = 0; i < ARRAY_SIZE(multi_bit_ecc_errors); i++) {
		ecc_error = &multi_bit_ecc_errors[i];
		if (irq_value & ecc_error->irq_msk) {
			val = hisi_sas_read32(hisi_hba, ecc_error->reg);
			val &= ecc_error->msk;
			val >>= ecc_error->shift;
			dev_err(dev, "%s (0x%x) found: mem addr is 0x%08X\n",
				ecc_error->msg, irq_value, val);
			queue_work(hisi_hba->wq, &hisi_hba->rst_work);
		}
	}

	return;
}