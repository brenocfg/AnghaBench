#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct qla_hw_data {TYPE_1__* pdev; } ;
struct TYPE_10__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_9__ {scalar_t__ subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_13 ; 
 int BIT_14 ; 
 int BIT_15 ; 
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA24XX_TYPE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA25XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA8044 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA81XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 scalar_t__ PCI_VENDOR_ID_HP ; 
 scalar_t__ PCI_VENDOR_ID_QLOGIC ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_mbx ; 
 int qla2x00_read_asic_temperature (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int qla2x00_read_sfp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  qla8044_read_temperature (TYPE_2__*) ; 
 int /*<<< orphan*/  qla82xx_read_temperature (TYPE_2__*) ; 

int
qla2x00_get_thermal_temp(scsi_qla_host_t *vha, uint16_t *temp)
{
	int rval = QLA_FUNCTION_FAILED;
	struct qla_hw_data *ha = vha->hw;
	uint8_t byte;

	if (!IS_FWI2_CAPABLE(ha) || IS_QLA24XX_TYPE(ha) || IS_QLA81XX(ha)) {
		ql_dbg(ql_dbg_mbx, vha, 0x1150,
		    "Thermal not supported by this card.\n");
		return rval;
	}

	if (IS_QLA25XX(ha)) {
		if (ha->pdev->subsystem_vendor == PCI_VENDOR_ID_QLOGIC &&
		    ha->pdev->subsystem_device == 0x0175) {
			rval = qla2x00_read_sfp(vha, 0, &byte,
			    0x98, 0x1, 1, BIT_13|BIT_0);
			*temp = byte;
			return rval;
		}
		if (ha->pdev->subsystem_vendor == PCI_VENDOR_ID_HP &&
		    ha->pdev->subsystem_device == 0x338e) {
			rval = qla2x00_read_sfp(vha, 0, &byte,
			    0x98, 0x1, 1, BIT_15|BIT_14|BIT_0);
			*temp = byte;
			return rval;
		}
		ql_dbg(ql_dbg_mbx, vha, 0x10c9,
		    "Thermal not supported by this card.\n");
		return rval;
	}

	if (IS_QLA82XX(ha)) {
		*temp = qla82xx_read_temperature(vha);
		rval = QLA_SUCCESS;
		return rval;
	} else if (IS_QLA8044(ha)) {
		*temp = qla8044_read_temperature(vha);
		rval = QLA_SUCCESS;
		return rval;
	}

	rval = qla2x00_read_asic_temperature(vha, temp);
	return rval;
}