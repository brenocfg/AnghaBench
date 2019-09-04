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
struct adf_cfg_section {int /*<<< orphan*/  list; int /*<<< orphan*/  param_head; int /*<<< orphan*/  name; } ;
struct adf_cfg_device_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  sec_list; } ;
struct adf_accel_dev {struct adf_cfg_device_data* cfg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct adf_cfg_section* adf_cfg_sec_find (struct adf_accel_dev*,char const*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct adf_cfg_section* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int adf_cfg_section_add(struct adf_accel_dev *accel_dev, const char *name)
{
	struct adf_cfg_device_data *cfg = accel_dev->cfg;
	struct adf_cfg_section *sec = adf_cfg_sec_find(accel_dev, name);

	if (sec)
		return 0;

	sec = kzalloc(sizeof(*sec), GFP_KERNEL);
	if (!sec)
		return -ENOMEM;

	strlcpy(sec->name, name, sizeof(sec->name));
	INIT_LIST_HEAD(&sec->param_head);
	down_write(&cfg->lock);
	list_add_tail(&sec->list, &cfg->sec_list);
	up_write(&cfg->lock);
	return 0;
}