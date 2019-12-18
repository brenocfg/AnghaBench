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
struct ti_sci_resource {int sets; TYPE_2__* desc; } ;
struct TYPE_3__ {scalar_t__ dev_index; } ;
struct msi_desc {int /*<<< orphan*/  list; TYPE_1__ inta; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int num; scalar_t__ start; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct msi_desc* alloc_msi_entry (struct device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_to_msi_list (struct device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_sci_inta_msi_free_descs (struct device*) ; 

__attribute__((used)) static int ti_sci_inta_msi_alloc_descs(struct device *dev,
				       struct ti_sci_resource *res)
{
	struct msi_desc *msi_desc;
	int set, i, count = 0;

	for (set = 0; set < res->sets; set++) {
		for (i = 0; i < res->desc[set].num; i++) {
			msi_desc = alloc_msi_entry(dev, 1, NULL);
			if (!msi_desc) {
				ti_sci_inta_msi_free_descs(dev);
				return -ENOMEM;
			}

			msi_desc->inta.dev_index = res->desc[set].start + i;
			INIT_LIST_HEAD(&msi_desc->list);
			list_add_tail(&msi_desc->list, dev_to_msi_list(dev));
			count++;
		}
	}

	return count;
}