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
struct TYPE_3__ {char* utf; char* dir; char* tcmd; } ;
struct TYPE_4__ {TYPE_1__ fw; } ;
struct ath6kl {int testmode; int /*<<< orphan*/  fw_len; int /*<<< orphan*/  fw; int /*<<< orphan*/  flag; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TESTMODE ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int,char*,int) ; 
 int ath6kl_get_fw (struct ath6kl*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_warn (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int ath6kl_fetch_testmode_file(struct ath6kl *ar)
{
	char filename[100];
	int ret;

	if (ar->testmode == 0)
		return 0;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "testmode %d\n", ar->testmode);

	if (ar->testmode == 2) {
		if (ar->hw.fw.utf == NULL) {
			ath6kl_warn("testmode 2 not supported\n");
			return -EOPNOTSUPP;
		}

		snprintf(filename, sizeof(filename), "%s/%s",
			 ar->hw.fw.dir, ar->hw.fw.utf);
	} else {
		if (ar->hw.fw.tcmd == NULL) {
			ath6kl_warn("testmode 1 not supported\n");
			return -EOPNOTSUPP;
		}

		snprintf(filename, sizeof(filename), "%s/%s",
			 ar->hw.fw.dir, ar->hw.fw.tcmd);
	}

	set_bit(TESTMODE, &ar->flag);

	ret = ath6kl_get_fw(ar, filename, &ar->fw, &ar->fw_len);
	if (ret) {
		ath6kl_err("Failed to get testmode %d firmware file %s: %d\n",
			   ar->testmode, filename, ret);
		return ret;
	}

	return 0;
}