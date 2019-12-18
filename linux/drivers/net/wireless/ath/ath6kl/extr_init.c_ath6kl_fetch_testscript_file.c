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
struct TYPE_3__ {char* testscript; char* dir; } ;
struct TYPE_4__ {TYPE_1__ fw; } ;
struct ath6kl {int testmode; int /*<<< orphan*/  fw_testscript_len; int /*<<< orphan*/ * fw_testscript; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_err (char*,char*,int) ; 
 int ath6kl_get_fw (struct ath6kl*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int ath6kl_fetch_testscript_file(struct ath6kl *ar)
{
	char filename[100];
	int ret;

	if (ar->testmode != 2)
		return 0;

	if (ar->fw_testscript != NULL)
		return 0;

	if (ar->hw.fw.testscript == NULL)
		return 0;

	snprintf(filename, sizeof(filename), "%s/%s",
		 ar->hw.fw.dir, ar->hw.fw.testscript);

	ret = ath6kl_get_fw(ar, filename, &ar->fw_testscript,
				&ar->fw_testscript_len);
	if (ret) {
		ath6kl_err("Failed to get testscript file %s: %d\n",
			   filename, ret);
		return ret;
	}

	return 0;
}