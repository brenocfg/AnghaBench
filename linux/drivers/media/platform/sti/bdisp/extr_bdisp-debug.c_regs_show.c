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
struct seq_file {struct bdisp_dev* private; } ;
struct bdisp_dev {int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLT_ACK ; 
 int /*<<< orphan*/  BLT_AQ1_CTL ; 
 int /*<<< orphan*/  BLT_AQ1_IP ; 
 int /*<<< orphan*/  BLT_AQ1_LNA ; 
 int /*<<< orphan*/  BLT_AQ1_STA ; 
 int /*<<< orphan*/  BLT_CIC ; 
 int /*<<< orphan*/  BLT_CTL ; 
 int /*<<< orphan*/  BLT_DEI ; 
 int /*<<< orphan*/  BLT_FCTL ; 
 scalar_t__ BLT_HFC_N ; 
 int /*<<< orphan*/  BLT_HFP ; 
 int /*<<< orphan*/  BLT_INS ; 
 int /*<<< orphan*/  BLT_ITM0 ; 
 int /*<<< orphan*/  BLT_ITS ; 
 int /*<<< orphan*/  BLT_IVMX0 ; 
 int /*<<< orphan*/  BLT_IVMX1 ; 
 int /*<<< orphan*/  BLT_IVMX2 ; 
 int /*<<< orphan*/  BLT_IVMX3 ; 
 unsigned int BLT_NB_H_COEF ; 
 unsigned int BLT_NB_V_COEF ; 
 int /*<<< orphan*/  BLT_NIP ; 
 int /*<<< orphan*/  BLT_OVMX0 ; 
 int /*<<< orphan*/  BLT_OVMX1 ; 
 int /*<<< orphan*/  BLT_OVMX2 ; 
 int /*<<< orphan*/  BLT_OVMX3 ; 
 int /*<<< orphan*/  BLT_PLUGS1_CHZ ; 
 int /*<<< orphan*/  BLT_PLUGS1_MSZ ; 
 int /*<<< orphan*/  BLT_PLUGS1_OP2 ; 
 int /*<<< orphan*/  BLT_PLUGS1_PGZ ; 
 int /*<<< orphan*/  BLT_PLUGS2_CHZ ; 
 int /*<<< orphan*/  BLT_PLUGS2_MSZ ; 
 int /*<<< orphan*/  BLT_PLUGS2_OP2 ; 
 int /*<<< orphan*/  BLT_PLUGS2_PGZ ; 
 int /*<<< orphan*/  BLT_PLUGS3_CHZ ; 
 int /*<<< orphan*/  BLT_PLUGS3_MSZ ; 
 int /*<<< orphan*/  BLT_PLUGS3_OP2 ; 
 int /*<<< orphan*/  BLT_PLUGS3_PGZ ; 
 int /*<<< orphan*/  BLT_PLUGT_CHZ ; 
 int /*<<< orphan*/  BLT_PLUGT_MSZ ; 
 int /*<<< orphan*/  BLT_PLUGT_OP2 ; 
 int /*<<< orphan*/  BLT_PLUGT_PGZ ; 
 int /*<<< orphan*/  BLT_RSF ; 
 int /*<<< orphan*/  BLT_RZI ; 
 int /*<<< orphan*/  BLT_S1BA ; 
 int /*<<< orphan*/  BLT_S1TY ; 
 int /*<<< orphan*/  BLT_S1XY ; 
 int /*<<< orphan*/  BLT_S2BA ; 
 int /*<<< orphan*/  BLT_S2SZ ; 
 int /*<<< orphan*/  BLT_S2TY ; 
 int /*<<< orphan*/  BLT_S2XY ; 
 int /*<<< orphan*/  BLT_S3BA ; 
 int /*<<< orphan*/  BLT_S3SZ ; 
 int /*<<< orphan*/  BLT_S3TY ; 
 int /*<<< orphan*/  BLT_S3XY ; 
 int /*<<< orphan*/  BLT_STA1 ; 
 int /*<<< orphan*/  BLT_TBA ; 
 int /*<<< orphan*/  BLT_TSZ ; 
 int /*<<< orphan*/  BLT_TTY ; 
 int /*<<< orphan*/  BLT_TXY ; 
 scalar_t__ BLT_VFC_N ; 
 int /*<<< orphan*/  BLT_VFP ; 
 scalar_t__ BLT_Y_HFC_N ; 
 int /*<<< orphan*/  BLT_Y_HFP ; 
 int /*<<< orphan*/  BLT_Y_RSF ; 
 int /*<<< orphan*/  BLT_Y_RZI ; 
 scalar_t__ BLT_Y_VFC_N ; 
 int /*<<< orphan*/  BLT_Y_VFP ; 
 int /*<<< orphan*/  DUMP (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int regs_show(struct seq_file *s, void *data)
{
	struct bdisp_dev *bdisp = s->private;
	int ret;
	unsigned int i;

	ret = pm_runtime_get_sync(bdisp->dev);
	if (ret < 0) {
		seq_puts(s, "Cannot wake up IP\n");
		return 0;
	}

	seq_printf(s, "Reg @ = 0x%p\n", bdisp->regs);

	seq_puts(s, "\nStatic:\n");
	DUMP(BLT_CTL);
	DUMP(BLT_ITS);
	DUMP(BLT_STA1);
	DUMP(BLT_AQ1_CTL);
	DUMP(BLT_AQ1_IP);
	DUMP(BLT_AQ1_LNA);
	DUMP(BLT_AQ1_STA);
	DUMP(BLT_ITM0);

	seq_puts(s, "\nPlugs:\n");
	DUMP(BLT_PLUGS1_OP2);
	DUMP(BLT_PLUGS1_CHZ);
	DUMP(BLT_PLUGS1_MSZ);
	DUMP(BLT_PLUGS1_PGZ);
	DUMP(BLT_PLUGS2_OP2);
	DUMP(BLT_PLUGS2_CHZ);
	DUMP(BLT_PLUGS2_MSZ);
	DUMP(BLT_PLUGS2_PGZ);
	DUMP(BLT_PLUGS3_OP2);
	DUMP(BLT_PLUGS3_CHZ);
	DUMP(BLT_PLUGS3_MSZ);
	DUMP(BLT_PLUGS3_PGZ);
	DUMP(BLT_PLUGT_OP2);
	DUMP(BLT_PLUGT_CHZ);
	DUMP(BLT_PLUGT_MSZ);
	DUMP(BLT_PLUGT_PGZ);

	seq_puts(s, "\nNode:\n");
	DUMP(BLT_NIP);
	DUMP(BLT_CIC);
	DUMP(BLT_INS);
	DUMP(BLT_ACK);
	DUMP(BLT_TBA);
	DUMP(BLT_TTY);
	DUMP(BLT_TXY);
	DUMP(BLT_TSZ);
	DUMP(BLT_S1BA);
	DUMP(BLT_S1TY);
	DUMP(BLT_S1XY);
	DUMP(BLT_S2BA);
	DUMP(BLT_S2TY);
	DUMP(BLT_S2XY);
	DUMP(BLT_S2SZ);
	DUMP(BLT_S3BA);
	DUMP(BLT_S3TY);
	DUMP(BLT_S3XY);
	DUMP(BLT_S3SZ);
	DUMP(BLT_FCTL);
	DUMP(BLT_RSF);
	DUMP(BLT_RZI);
	DUMP(BLT_HFP);
	DUMP(BLT_VFP);
	DUMP(BLT_Y_RSF);
	DUMP(BLT_Y_RZI);
	DUMP(BLT_Y_HFP);
	DUMP(BLT_Y_VFP);
	DUMP(BLT_IVMX0);
	DUMP(BLT_IVMX1);
	DUMP(BLT_IVMX2);
	DUMP(BLT_IVMX3);
	DUMP(BLT_OVMX0);
	DUMP(BLT_OVMX1);
	DUMP(BLT_OVMX2);
	DUMP(BLT_OVMX3);
	DUMP(BLT_DEI);

	seq_puts(s, "\nFilter:\n");
	for (i = 0; i < BLT_NB_H_COEF; i++) {
		seq_printf(s, "BLT_HFC%d \t0x%08X\n", i,
			   readl(bdisp->regs + BLT_HFC_N + i * 4));
	}
	for (i = 0; i < BLT_NB_V_COEF; i++) {
		seq_printf(s, "BLT_VFC%d \t0x%08X\n", i,
			   readl(bdisp->regs + BLT_VFC_N + i * 4));
	}

	seq_puts(s, "\nLuma filter:\n");
	for (i = 0; i < BLT_NB_H_COEF; i++) {
		seq_printf(s, "BLT_Y_HFC%d \t0x%08X\n", i,
			   readl(bdisp->regs + BLT_Y_HFC_N + i * 4));
	}
	for (i = 0; i < BLT_NB_V_COEF; i++) {
		seq_printf(s, "BLT_Y_VFC%d \t0x%08X\n", i,
			   readl(bdisp->regs + BLT_Y_VFC_N + i * 4));
	}

	pm_runtime_put(bdisp->dev);

	return 0;
}