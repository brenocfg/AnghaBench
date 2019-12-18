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
struct TYPE_2__ {char* fw_board; char* fw_default_board; } ;
struct ath6kl {int /*<<< orphan*/  fw_board_len; int /*<<< orphan*/ * fw_board; TYPE_1__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*,char const*,int) ; 
 int ath6kl_get_fw (struct ath6kl*,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,...) ; 
 scalar_t__ check_device_tree (struct ath6kl*) ; 

__attribute__((used)) static int ath6kl_fetch_board_file(struct ath6kl *ar)
{
	const char *filename;
	int ret;

	if (ar->fw_board != NULL)
		return 0;

	if (WARN_ON(ar->hw.fw_board == NULL))
		return -EINVAL;

	filename = ar->hw.fw_board;

	ret = ath6kl_get_fw(ar, filename, &ar->fw_board,
			    &ar->fw_board_len);
	if (ret == 0) {
		/* managed to get proper board file */
		return 0;
	}

	if (check_device_tree(ar)) {
		/* got board file from device tree */
		return 0;
	}

	/* there was no proper board file, try to use default instead */
	ath6kl_warn("Failed to get board file %s (%d), trying to find default board file.\n",
		    filename, ret);

	filename = ar->hw.fw_default_board;

	ret = ath6kl_get_fw(ar, filename, &ar->fw_board,
			    &ar->fw_board_len);
	if (ret) {
		ath6kl_err("Failed to get default board file %s: %d\n",
			   filename, ret);
		return ret;
	}

	ath6kl_warn("WARNING! No proper board file was not found, instead using a default board file.\n");
	ath6kl_warn("Most likely your hardware won't work as specified. Install correct board file!\n");

	return 0;
}