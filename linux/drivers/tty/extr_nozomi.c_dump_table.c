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
struct TYPE_3__ {int /*<<< orphan*/  diag_dl; int /*<<< orphan*/  mdm_dl; int /*<<< orphan*/  mdm_ul; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  ul_ctrl_len; int /*<<< orphan*/  ul_app2_len; int /*<<< orphan*/  ul_app1_len; int /*<<< orphan*/  ul_diag_len; int /*<<< orphan*/  ul_mdm_len2; int /*<<< orphan*/  ul_mdm_len1; int /*<<< orphan*/  ul_start; int /*<<< orphan*/  dl_ctrl_len; int /*<<< orphan*/  dl_app2_len; int /*<<< orphan*/  dl_app1_len; int /*<<< orphan*/  dl_diag_len2; int /*<<< orphan*/  dl_diag_len1; int /*<<< orphan*/  dl_mdm_len2; int /*<<< orphan*/  dl_mdm_len1; int /*<<< orphan*/  dl_start; TYPE_1__ toggle; int /*<<< orphan*/  product_information; int /*<<< orphan*/  version; int /*<<< orphan*/  signature; } ;
struct nozomi {TYPE_2__ config_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG3 (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void dump_table(const struct nozomi *dc)
{
	DBG3("signature: 0x%08X", dc->config_table.signature);
	DBG3("version: 0x%04X", dc->config_table.version);
	DBG3("product_information: 0x%04X", \
				dc->config_table.product_information);
	DBG3("toggle enabled: %d", dc->config_table.toggle.enabled);
	DBG3("toggle up_mdm: %d", dc->config_table.toggle.mdm_ul);
	DBG3("toggle dl_mdm: %d", dc->config_table.toggle.mdm_dl);
	DBG3("toggle dl_dbg: %d", dc->config_table.toggle.diag_dl);

	DBG3("dl_start: 0x%04X", dc->config_table.dl_start);
	DBG3("dl_mdm_len0: 0x%04X, %d", dc->config_table.dl_mdm_len1,
	   dc->config_table.dl_mdm_len1);
	DBG3("dl_mdm_len1: 0x%04X, %d", dc->config_table.dl_mdm_len2,
	   dc->config_table.dl_mdm_len2);
	DBG3("dl_diag_len0: 0x%04X, %d", dc->config_table.dl_diag_len1,
	   dc->config_table.dl_diag_len1);
	DBG3("dl_diag_len1: 0x%04X, %d", dc->config_table.dl_diag_len2,
	   dc->config_table.dl_diag_len2);
	DBG3("dl_app1_len: 0x%04X, %d", dc->config_table.dl_app1_len,
	   dc->config_table.dl_app1_len);
	DBG3("dl_app2_len: 0x%04X, %d", dc->config_table.dl_app2_len,
	   dc->config_table.dl_app2_len);
	DBG3("dl_ctrl_len: 0x%04X, %d", dc->config_table.dl_ctrl_len,
	   dc->config_table.dl_ctrl_len);
	DBG3("ul_start: 0x%04X, %d", dc->config_table.ul_start,
	   dc->config_table.ul_start);
	DBG3("ul_mdm_len[0]: 0x%04X, %d", dc->config_table.ul_mdm_len1,
	   dc->config_table.ul_mdm_len1);
	DBG3("ul_mdm_len[1]: 0x%04X, %d", dc->config_table.ul_mdm_len2,
	   dc->config_table.ul_mdm_len2);
	DBG3("ul_diag_len: 0x%04X, %d", dc->config_table.ul_diag_len,
	   dc->config_table.ul_diag_len);
	DBG3("ul_app1_len: 0x%04X, %d", dc->config_table.ul_app1_len,
	   dc->config_table.ul_app1_len);
	DBG3("ul_app2_len: 0x%04X, %d", dc->config_table.ul_app2_len,
	   dc->config_table.ul_app2_len);
	DBG3("ul_ctrl_len: 0x%04X, %d", dc->config_table.ul_ctrl_len,
	   dc->config_table.ul_ctrl_len);
}