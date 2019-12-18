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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int u64 ;
struct qla_hw_data {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_CTL_CHECK ; 
 int MIU_TA_CTL_BUSY ; 
 int MIU_TA_CTL_ENABLE ; 
 int MIU_TA_CTL_START ; 
 int MIU_TA_CTL_WRITE ; 
 int MIU_TEST_AGT_ADDR_HI ; 
 int MIU_TEST_AGT_ADDR_LO ; 
 int MIU_TEST_AGT_CTRL ; 
 int MIU_TEST_AGT_WRDATA_HI ; 
 int MIU_TEST_AGT_WRDATA_LO ; 
 int MIU_TEST_AGT_WRDATA_UPPER_HI ; 
 int MIU_TEST_AGT_WRDATA_UPPER_LO ; 
 int QLA82XX_ADDR_QDR_NET ; 
 int QLA82XX_CRB_DDR_NET ; 
 int QLA82XX_CRB_QDR_NET ; 
 int QLA82XX_P3_ADDR_QDR_NET_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ printk_ratelimit () ; 
 scalar_t__ qla82xx_pci_mem_bound_check (struct qla_hw_data*,int,int) ; 
 scalar_t__ qla82xx_pci_mem_read_2M (struct qla_hw_data*,int,int*,int) ; 
 int qla82xx_pci_mem_write_direct (struct qla_hw_data*,int,void*,int) ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int,int) ; 

__attribute__((used)) static int
qla82xx_pci_mem_write_2M(struct qla_hw_data *ha,
		u64 off, void *data, int size)
{
	int i, j, ret = 0, loop, sz[2], off0;
	int scale, shift_amount, startword;
	uint32_t temp;
	uint64_t off8, mem_crb, tmpw, word[2] = {0, 0};

	/*
	 * If not MN, go check for MS or invalid.
	 */
	if (off >= QLA82XX_ADDR_QDR_NET && off <= QLA82XX_P3_ADDR_QDR_NET_MAX)
		mem_crb = QLA82XX_CRB_QDR_NET;
	else {
		mem_crb = QLA82XX_CRB_DDR_NET;
		if (qla82xx_pci_mem_bound_check(ha, off, size) == 0)
			return qla82xx_pci_mem_write_direct(ha,
			    off, data, size);
	}

	off0 = off & 0x7;
	sz[0] = (size < (8 - off0)) ? size : (8 - off0);
	sz[1] = size - sz[0];

	off8 = off & 0xfffffff0;
	loop = (((off & 0xf) + size - 1) >> 4) + 1;
	shift_amount = 4;
	scale = 2;
	startword = (off & 0xf)/8;

	for (i = 0; i < loop; i++) {
		if (qla82xx_pci_mem_read_2M(ha, off8 +
		    (i << shift_amount), &word[i * scale], 8))
			return -1;
	}

	switch (size) {
	case 1:
		tmpw = *((uint8_t *)data);
		break;
	case 2:
		tmpw = *((uint16_t *)data);
		break;
	case 4:
		tmpw = *((uint32_t *)data);
		break;
	case 8:
	default:
		tmpw = *((uint64_t *)data);
		break;
	}

	if (sz[0] == 8) {
		word[startword] = tmpw;
	} else {
		word[startword] &=
			~((~(~0ULL << (sz[0] * 8))) << (off0 * 8));
		word[startword] |= tmpw << (off0 * 8);
	}
	if (sz[1] != 0) {
		word[startword+1] &= ~(~0ULL << (sz[1] * 8));
		word[startword+1] |= tmpw >> (sz[0] * 8);
	}

	for (i = 0; i < loop; i++) {
		temp = off8 + (i << shift_amount);
		qla82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_ADDR_LO, temp);
		temp = 0;
		qla82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_ADDR_HI, temp);
		temp = word[i * scale] & 0xffffffff;
		qla82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_WRDATA_LO, temp);
		temp = (word[i * scale] >> 32) & 0xffffffff;
		qla82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_WRDATA_HI, temp);
		temp = word[i*scale + 1] & 0xffffffff;
		qla82xx_wr_32(ha, mem_crb +
		    MIU_TEST_AGT_WRDATA_UPPER_LO, temp);
		temp = (word[i*scale + 1] >> 32) & 0xffffffff;
		qla82xx_wr_32(ha, mem_crb +
		    MIU_TEST_AGT_WRDATA_UPPER_HI, temp);

		temp = MIU_TA_CTL_ENABLE | MIU_TA_CTL_WRITE;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);
		temp = MIU_TA_CTL_START | MIU_TA_CTL_ENABLE | MIU_TA_CTL_WRITE;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);

		for (j = 0; j < MAX_CTL_CHECK; j++) {
			temp = qla82xx_rd_32(ha, mem_crb + MIU_TEST_AGT_CTRL);
			if ((temp & MIU_TA_CTL_BUSY) == 0)
				break;
		}

		if (j >= MAX_CTL_CHECK) {
			if (printk_ratelimit())
				dev_err(&ha->pdev->dev,
				    "failed to write through agent.\n");
			ret = -1;
			break;
		}
	}

	return ret;
}