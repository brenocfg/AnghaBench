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
struct ntb_msi_devres {struct msi_desc* entry; struct ntb_msi_desc* msi_desc; struct ntb_dev* ntb; } ;
struct ntb_msi_desc {int dummy; } ;
struct ntb_dev {int /*<<< orphan*/  dev; } ;
struct msi_desc {struct ntb_msi_devres* write_msi_msg_data; int /*<<< orphan*/  write_msi_msg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devres_add (int /*<<< orphan*/ *,struct ntb_msi_devres*) ; 
 struct ntb_msi_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_msi_write_msg ; 
 int /*<<< orphan*/  ntbm_msi_callback_release ; 

__attribute__((used)) static int ntbm_msi_setup_callback(struct ntb_dev *ntb, struct msi_desc *entry,
				   struct ntb_msi_desc *msi_desc)
{
	struct ntb_msi_devres *dr;

	dr = devres_alloc(ntbm_msi_callback_release,
			  sizeof(struct ntb_msi_devres), GFP_KERNEL);
	if (!dr)
		return -ENOMEM;

	dr->ntb = ntb;
	dr->entry = entry;
	dr->msi_desc = msi_desc;

	devres_add(&ntb->dev, dr);

	dr->entry->write_msi_msg = ntb_msi_write_msg;
	dr->entry->write_msi_msg_data = dr;

	return 0;
}