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
typedef  scalar_t__ u32 ;
struct lbs_fw_table {scalar_t__ model; int /*<<< orphan*/ * fwname; int /*<<< orphan*/ * helper; } ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ *,struct device*) ; 

int lbs_get_firmware(struct device *dev, u32 card_model,
			const struct lbs_fw_table *fw_table,
			const struct firmware **helper,
			const struct firmware **mainfw)
{
	const struct lbs_fw_table *iter;
	int ret;

	BUG_ON(helper == NULL);
	BUG_ON(mainfw == NULL);

	/* Search for firmware to use from the table. */
	iter = fw_table;
	while (iter && iter->helper) {
		if (iter->model != card_model)
			goto next;

		if (*helper == NULL) {
			ret = request_firmware(helper, iter->helper, dev);
			if (ret)
				goto next;

			/* If the device has one-stage firmware (ie cf8305) and
			 * we've got it then we don't need to bother with the
			 * main firmware.
			 */
			if (iter->fwname == NULL)
				return 0;
		}

		if (*mainfw == NULL) {
			ret = request_firmware(mainfw, iter->fwname, dev);
			if (ret) {
				/* Clear the helper to ensure we don't have
				 * mismatched firmware pairs.
				 */
				release_firmware(*helper);
				*helper = NULL;
			}
		}

		if (*helper && *mainfw)
			return 0;

  next:
		iter++;
	}

	/* Failed */
	release_firmware(*helper);
	*helper = NULL;
	release_firmware(*mainfw);
	*mainfw = NULL;

	return -ENOENT;
}