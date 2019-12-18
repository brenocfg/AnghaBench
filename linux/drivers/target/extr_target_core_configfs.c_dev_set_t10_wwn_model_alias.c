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
struct TYPE_4__ {int /*<<< orphan*/  model; } ;
struct TYPE_3__ {int /*<<< orphan*/  cg_item; } ;
struct se_device {TYPE_2__ t10_wwn; TYPE_1__ dev_group; } ;

/* Variables and functions */
 scalar_t__ INQUIRY_MODEL_LEN ; 
 char* config_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,struct se_device*,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void dev_set_t10_wwn_model_alias(struct se_device *dev)
{
	const char *configname;

	configname = config_item_name(&dev->dev_group.cg_item);
	if (strlen(configname) >= INQUIRY_MODEL_LEN) {
		pr_warn("dev[%p]: Backstore name '%s' is too long for "
			"INQUIRY_MODEL, truncating to 15 characters\n", dev,
			configname);
	}
	/*
	 * XXX We can't use sizeof(dev->t10_wwn.model) (INQUIRY_MODEL_LEN + 1)
	 * here without potentially breaking existing setups, so continue to
	 * truncate one byte shorter than what can be carried in INQUIRY.
	 */
	strlcpy(dev->t10_wwn.model, configname, INQUIRY_MODEL_LEN);
}