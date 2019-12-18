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
struct TYPE_2__ {int hash_filter; int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int ACTIVEFILTERCOUNTS_F ; 
 int HASH_ACTV_HIT_G (int) ; 
 int /*<<< orphan*/  LE_DB_RSP_CODE_0_A ; 
 int /*<<< orphan*/  LE_DB_RSP_CODE_1_A ; 
 int TCAM_ACTV_HIT_G (int) ; 
 int /*<<< orphan*/  TP_GLOBAL_CONFIG_A ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_offload (struct adapter*) ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

void init_hash_filter(struct adapter *adap)
{
	u32 reg;

	/* On T6, verify the necessary register configs and warn the user in
	 * case of improper config
	 */
	if (is_t6(adap->params.chip)) {
		if (is_offload(adap)) {
			if (!(t4_read_reg(adap, TP_GLOBAL_CONFIG_A)
			   & ACTIVEFILTERCOUNTS_F)) {
				dev_err(adap->pdev_dev, "Invalid hash filter + ofld config\n");
				return;
			}
		} else {
			reg = t4_read_reg(adap, LE_DB_RSP_CODE_0_A);
			if (TCAM_ACTV_HIT_G(reg) != 4) {
				dev_err(adap->pdev_dev, "Invalid hash filter config\n");
				return;
			}

			reg = t4_read_reg(adap, LE_DB_RSP_CODE_1_A);
			if (HASH_ACTV_HIT_G(reg) != 4) {
				dev_err(adap->pdev_dev, "Invalid hash filter config\n");
				return;
			}
		}

	} else {
		dev_err(adap->pdev_dev, "Hash filter supported only on T6\n");
		return;
	}

	adap->params.hash_filter = 1;
}