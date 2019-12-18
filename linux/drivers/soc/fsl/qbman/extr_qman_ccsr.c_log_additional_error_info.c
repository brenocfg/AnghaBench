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
typedef  int u32 ;
struct qm_ecir2 {void* info; } ;
struct qm_ecir {void* info; } ;
struct qm_eadr {void* info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {char* txt; int addr_mask; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int FQID_ECSR_ERR ; 
 int PORTAL_ECSR_ERR ; 
 int QMAN_REV30 ; 
 int QM_EIRQ_IECE ; 
 int QM_EIRQ_MBEI ; 
 int QM_EIRQ_SBEI ; 
 int /*<<< orphan*/  REG_EADR ; 
 int /*<<< orphan*/  REG_ECIR ; 
 int /*<<< orphan*/  REG_ECIR2 ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*,...) ; 
 TYPE_1__* error_mdata ; 
 int /*<<< orphan*/  log_edata_bits (struct device*,int /*<<< orphan*/ ) ; 
 void* qm_ccsr_in (int /*<<< orphan*/ ) ; 
 int qm_eadr_get_eadr (struct qm_eadr*) ; 
 int qm_eadr_get_memid (struct qm_eadr*) ; 
 int qm_eadr_v3_get_eadr (struct qm_eadr*) ; 
 int qm_eadr_v3_get_memid (struct qm_eadr*) ; 
 int qm_ecir2_get_pnum (struct qm_ecir2*) ; 
 scalar_t__ qm_ecir2_is_dcp (struct qm_ecir2*) ; 
 int /*<<< orphan*/  qm_ecir_get_fqid (struct qm_ecir*) ; 
 int qm_ecir_get_pnum (struct qm_ecir*) ; 
 scalar_t__ qm_ecir_is_dcp (struct qm_ecir*) ; 
 int qman_ip_rev ; 

__attribute__((used)) static void log_additional_error_info(struct device *dev, u32 isr_val,
				      u32 ecsr_val)
{
	struct qm_ecir ecir_val;
	struct qm_eadr eadr_val;
	int memid;

	ecir_val.info = qm_ccsr_in(REG_ECIR);
	/* Is portal info valid */
	if ((qman_ip_rev & 0xFF00) >= QMAN_REV30) {
		struct qm_ecir2 ecir2_val;

		ecir2_val.info = qm_ccsr_in(REG_ECIR2);
		if (ecsr_val & PORTAL_ECSR_ERR) {
			dev_warn(dev, "ErrInt: %s id %d\n",
				 qm_ecir2_is_dcp(&ecir2_val) ? "DCP" : "SWP",
				 qm_ecir2_get_pnum(&ecir2_val));
		}
		if (ecsr_val & (FQID_ECSR_ERR | QM_EIRQ_IECE))
			dev_warn(dev, "ErrInt: ecir.fqid 0x%x\n",
				 qm_ecir_get_fqid(&ecir_val));

		if (ecsr_val & (QM_EIRQ_SBEI|QM_EIRQ_MBEI)) {
			eadr_val.info = qm_ccsr_in(REG_EADR);
			memid = qm_eadr_v3_get_memid(&eadr_val);
			dev_warn(dev, "ErrInt: EADR Memory: %s, 0x%x\n",
				 error_mdata[memid].txt,
				 error_mdata[memid].addr_mask
					& qm_eadr_v3_get_eadr(&eadr_val));
			log_edata_bits(dev, error_mdata[memid].bits);
		}
	} else {
		if (ecsr_val & PORTAL_ECSR_ERR) {
			dev_warn(dev, "ErrInt: %s id %d\n",
				 qm_ecir_is_dcp(&ecir_val) ? "DCP" : "SWP",
				 qm_ecir_get_pnum(&ecir_val));
		}
		if (ecsr_val & FQID_ECSR_ERR)
			dev_warn(dev, "ErrInt: ecir.fqid 0x%x\n",
				 qm_ecir_get_fqid(&ecir_val));

		if (ecsr_val & (QM_EIRQ_SBEI|QM_EIRQ_MBEI)) {
			eadr_val.info = qm_ccsr_in(REG_EADR);
			memid = qm_eadr_get_memid(&eadr_val);
			dev_warn(dev, "ErrInt: EADR Memory: %s, 0x%x\n",
				 error_mdata[memid].txt,
				 error_mdata[memid].addr_mask
					& qm_eadr_get_eadr(&eadr_val));
			log_edata_bits(dev, error_mdata[memid].bits);
		}
	}
}