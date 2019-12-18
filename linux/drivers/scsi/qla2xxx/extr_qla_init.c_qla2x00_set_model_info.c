#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zero ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;
struct qla_hw_data {char* model_number; char* model_desc; TYPE_1__* pdev; } ;
struct TYPE_6__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_5__ {int subsystem_device; scalar_t__ subsystem_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA2031 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA24XX_TYPE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA25XX (struct qla_hw_data*) ; 
 scalar_t__ PCI_VENDOR_ID_QLOGIC ; 
 int QLA_MODEL_NAMES ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 char const** qla2x00_model_name ; 
 int /*<<< orphan*/  qla2xxx_get_vpd_field (TYPE_2__*,char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

inline void
qla2x00_set_model_info(scsi_qla_host_t *vha, uint8_t *model, size_t len,
		       const char *def)
{
	char *st, *en;
	uint16_t index;
	uint64_t zero[2] = { 0 };
	struct qla_hw_data *ha = vha->hw;
	int use_tbl = !IS_QLA24XX_TYPE(ha) && !IS_QLA25XX(ha) &&
	    !IS_CNA_CAPABLE(ha) && !IS_QLA2031(ha);

	if (len > sizeof(zero))
		len = sizeof(zero);
	if (memcmp(model, &zero, len) != 0) {
		memcpy(ha->model_number, model, len);
		st = en = ha->model_number;
		en += len - 1;
		while (en > st) {
			if (*en != 0x20 && *en != 0x00)
				break;
			*en-- = '\0';
		}

		index = (ha->pdev->subsystem_device & 0xff);
		if (use_tbl &&
		    ha->pdev->subsystem_vendor == PCI_VENDOR_ID_QLOGIC &&
		    index < QLA_MODEL_NAMES)
			strlcpy(ha->model_desc,
			    qla2x00_model_name[index * 2 + 1],
			    sizeof(ha->model_desc));
	} else {
		index = (ha->pdev->subsystem_device & 0xff);
		if (use_tbl &&
		    ha->pdev->subsystem_vendor == PCI_VENDOR_ID_QLOGIC &&
		    index < QLA_MODEL_NAMES) {
			strlcpy(ha->model_number,
				qla2x00_model_name[index * 2],
				sizeof(ha->model_number));
			strlcpy(ha->model_desc,
			    qla2x00_model_name[index * 2 + 1],
			    sizeof(ha->model_desc));
		} else {
			strlcpy(ha->model_number, def,
				sizeof(ha->model_number));
		}
	}
	if (IS_FWI2_CAPABLE(ha))
		qla2xxx_get_vpd_field(vha, "\x82", ha->model_desc,
		    sizeof(ha->model_desc));
}