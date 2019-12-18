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
struct hns_roce_link_table_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  map; scalar_t__ buf; } ;
struct hns_roce_link_table {int npages; int pg_sz; TYPE_1__ table; TYPE_2__* pg_list; } ;
struct hns_roce_dev {struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  map; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void hns_roce_free_link_table(struct hns_roce_dev *hr_dev,
				     struct hns_roce_link_table *link_tbl)
{
	struct device *dev = hr_dev->dev;
	int size;
	int i;

	size = link_tbl->npages * sizeof(struct hns_roce_link_table_entry);

	for (i = 0; i < link_tbl->npages; ++i)
		if (link_tbl->pg_list[i].buf)
			dma_free_coherent(dev, link_tbl->pg_sz,
					  link_tbl->pg_list[i].buf,
					  link_tbl->pg_list[i].map);
	kfree(link_tbl->pg_list);

	dma_free_coherent(dev, size, link_tbl->table.buf,
			  link_tbl->table.map);
}