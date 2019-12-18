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
struct hns_roce_db_pgdir {int /*<<< orphan*/  page; int /*<<< orphan*/  db_dma; int /*<<< orphan*/  order1; int /*<<< orphan*/ * bits; int /*<<< orphan*/  order0; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HNS_ROCE_DB_PER_PAGE ; 
 int HNS_ROCE_DB_TYPE_COUNT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_db_pgdir*) ; 
 struct hns_roce_db_pgdir* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hns_roce_db_pgdir *hns_roce_alloc_db_pgdir(
					struct device *dma_device)
{
	struct hns_roce_db_pgdir *pgdir;

	pgdir = kzalloc(sizeof(*pgdir), GFP_KERNEL);
	if (!pgdir)
		return NULL;

	bitmap_fill(pgdir->order1,
		    HNS_ROCE_DB_PER_PAGE / HNS_ROCE_DB_TYPE_COUNT);
	pgdir->bits[0] = pgdir->order0;
	pgdir->bits[1] = pgdir->order1;
	pgdir->page = dma_alloc_coherent(dma_device, PAGE_SIZE,
					 &pgdir->db_dma, GFP_KERNEL);
	if (!pgdir->page) {
		kfree(pgdir);
		return NULL;
	}

	return pgdir;
}