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
typedef  int /*<<< orphan*/  u32 ;
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sw_mstr_rst_mask; int /*<<< orphan*/  rst_src_en_mask; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  regmap ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* reset_masks ; 
 int /*<<< orphan*/  rst_src_en ; 
 int /*<<< orphan*/  sw_mstr_rst ; 

__attribute__((used)) static int brcmstb_restart_handler(struct notifier_block *this,
				   unsigned long mode, void *cmd)
{
	int rc;
	u32 tmp;

	rc = regmap_write(regmap, rst_src_en, reset_masks->rst_src_en_mask);
	if (rc) {
		pr_err("failed to write rst_src_en (%d)\n", rc);
		return NOTIFY_DONE;
	}

	rc = regmap_read(regmap, rst_src_en, &tmp);
	if (rc) {
		pr_err("failed to read rst_src_en (%d)\n", rc);
		return NOTIFY_DONE;
	}

	rc = regmap_write(regmap, sw_mstr_rst, reset_masks->sw_mstr_rst_mask);
	if (rc) {
		pr_err("failed to write sw_mstr_rst (%d)\n", rc);
		return NOTIFY_DONE;
	}

	rc = regmap_read(regmap, sw_mstr_rst, &tmp);
	if (rc) {
		pr_err("failed to read sw_mstr_rst (%d)\n", rc);
		return NOTIFY_DONE;
	}

	while (1)
		;

	return NOTIFY_DONE;
}