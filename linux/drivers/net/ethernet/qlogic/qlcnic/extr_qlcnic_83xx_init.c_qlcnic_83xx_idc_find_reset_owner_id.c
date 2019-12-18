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
struct qlcnic_adapter {int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_TYPE_FCOE ; 
 int QLCNIC_TYPE_ISCSI ; 
 int QLCNIC_TYPE_NIC ; 
 int QLCRDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_IDC_DEV_PARTITION_INFO_1 ; 
 int /*<<< orphan*/  QLC_83XX_IDC_DEV_PARTITION_INFO_2 ; 
 int QLC_83XX_IDC_MAX_CNA_FUNCTIONS ; 
 int QLC_83XX_IDC_MAX_FUNC_PER_PARTITION_INFO ; 

__attribute__((used)) static int qlcnic_83xx_idc_find_reset_owner_id(struct qlcnic_adapter *adapter)
{
	u32 reg, reg1, reg2, i, j, owner, class;

	reg1 = QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_PARTITION_INFO_1);
	reg2 = QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_PARTITION_INFO_2);
	owner = QLCNIC_TYPE_NIC;
	i = 0;
	j = 0;
	reg = reg1;

	do {
		class = (((reg & (0xF << j * 4)) >> j * 4) & 0x3);
		if (class == owner)
			break;
		if (i == (QLC_83XX_IDC_MAX_FUNC_PER_PARTITION_INFO - 1)) {
			reg = reg2;
			j = 0;
		} else {
			j++;
		}

		if (i == (QLC_83XX_IDC_MAX_CNA_FUNCTIONS - 1)) {
			if (owner == QLCNIC_TYPE_NIC)
				owner = QLCNIC_TYPE_ISCSI;
			else if (owner == QLCNIC_TYPE_ISCSI)
				owner = QLCNIC_TYPE_FCOE;
			else if (owner == QLCNIC_TYPE_FCOE)
				return -EIO;
			reg = reg1;
			j = 0;
			i = 0;
		}
	} while (i++ < QLC_83XX_IDC_MAX_CNA_FUNCTIONS);

	return i;
}