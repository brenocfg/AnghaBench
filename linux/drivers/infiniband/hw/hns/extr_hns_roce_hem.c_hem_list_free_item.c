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
struct roce_hem_item {int count; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  addr; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct roce_hem_item*) ; 

__attribute__((used)) static void hem_list_free_item(struct hns_roce_dev *hr_dev,
			       struct roce_hem_item *hem, bool exist_bt)
{
	if (exist_bt)
		dma_free_coherent(hr_dev->dev, hem->count * BA_BYTE_LEN,
				  hem->addr, hem->dma_addr);
	kfree(hem);
}