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
struct net_device {int dummy; } ;
struct hwrm_selftest_qlist_output {int num_tests; int offline_tests; char* test0_name; int /*<<< orphan*/  test_timeout; } ;
struct hwrm_selftest_qlist_input {int /*<<< orphan*/  member_0; } ;
struct bnxt_test_info {int offline_mask; char** string; scalar_t__ timeout; } ;
struct bnxt {int fw_cap; int num_tests; int hwrm_spec_code; int /*<<< orphan*/  hwrm_cmd_lock; struct bnxt_test_info* test_info; struct net_device* dev; struct hwrm_selftest_qlist_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_DRV_TESTS ; 
 int BNXT_EXTLPBK_TEST_IDX ; 
 int BNXT_FW_CAP_PKG_VER ; 
 int BNXT_IRQ_TEST_IDX ; 
 int BNXT_MACLPBK_TEST_IDX ; 
 int BNXT_MAX_TEST ; 
 int BNXT_PHYLPBK_TEST_IDX ; 
 int /*<<< orphan*/  BNXT_SINGLE_PF (struct bnxt*) ; 
 scalar_t__ ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_SELFTEST_QLIST ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_selftest_qlist_input*,int,scalar_t__) ; 
 int /*<<< orphan*/  bnxt_get_pkgver (struct net_device*) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_selftest_qlist_input*,int /*<<< orphan*/ ,int,int) ; 
 struct bnxt_test_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,scalar_t__) ; 

void bnxt_ethtool_init(struct bnxt *bp)
{
	struct hwrm_selftest_qlist_output *resp = bp->hwrm_cmd_resp_addr;
	struct hwrm_selftest_qlist_input req = {0};
	struct bnxt_test_info *test_info;
	struct net_device *dev = bp->dev;
	int i, rc;

	if (!(bp->fw_cap & BNXT_FW_CAP_PKG_VER))
		bnxt_get_pkgver(dev);

	bp->num_tests = 0;
	if (bp->hwrm_spec_code < 0x10704 || !BNXT_SINGLE_PF(bp))
		return;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_SELFTEST_QLIST, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		goto ethtool_init_exit;

	test_info = bp->test_info;
	if (!test_info)
		test_info = kzalloc(sizeof(*bp->test_info), GFP_KERNEL);
	if (!test_info)
		goto ethtool_init_exit;

	bp->test_info = test_info;
	bp->num_tests = resp->num_tests + BNXT_DRV_TESTS;
	if (bp->num_tests > BNXT_MAX_TEST)
		bp->num_tests = BNXT_MAX_TEST;

	test_info->offline_mask = resp->offline_tests;
	test_info->timeout = le16_to_cpu(resp->test_timeout);
	if (!test_info->timeout)
		test_info->timeout = HWRM_CMD_TIMEOUT;
	for (i = 0; i < bp->num_tests; i++) {
		char *str = test_info->string[i];
		char *fw_str = resp->test0_name + i * 32;

		if (i == BNXT_MACLPBK_TEST_IDX) {
			strcpy(str, "Mac loopback test (offline)");
		} else if (i == BNXT_PHYLPBK_TEST_IDX) {
			strcpy(str, "Phy loopback test (offline)");
		} else if (i == BNXT_EXTLPBK_TEST_IDX) {
			strcpy(str, "Ext loopback test (offline)");
		} else if (i == BNXT_IRQ_TEST_IDX) {
			strcpy(str, "Interrupt_test (offline)");
		} else {
			strlcpy(str, fw_str, ETH_GSTRING_LEN);
			strncat(str, " test", ETH_GSTRING_LEN - strlen(str));
			if (test_info->offline_mask & (1 << i))
				strncat(str, " (offline)",
					ETH_GSTRING_LEN - strlen(str));
			else
				strncat(str, " (online)",
					ETH_GSTRING_LEN - strlen(str));
		}
	}

ethtool_init_exit:
	mutex_unlock(&bp->hwrm_cmd_lock);
}