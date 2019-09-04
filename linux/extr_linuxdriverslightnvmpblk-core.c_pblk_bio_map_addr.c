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
struct pblk {struct nvm_tgt_dev* dev; } ;
struct page {int dummy; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  q; } ;
struct bio {int /*<<< orphan*/  bi_end_io; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct bio* ERR_PTR (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int PBLK_KMALLOC_META ; 
 int bio_add_pc_page (int /*<<< orphan*/ ,struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_kmalloc (int /*<<< orphan*/ ,unsigned int) ; 
 struct bio* bio_map_kern (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  pblk_bio_map_addr_endio ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 struct page* vmalloc_to_page (void*) ; 

struct bio *pblk_bio_map_addr(struct pblk *pblk, void *data,
			      unsigned int nr_secs, unsigned int len,
			      int alloc_type, gfp_t gfp_mask)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	void *kaddr = data;
	struct page *page;
	struct bio *bio;
	int i, ret;

	if (alloc_type == PBLK_KMALLOC_META)
		return bio_map_kern(dev->q, kaddr, len, gfp_mask);

	bio = bio_kmalloc(gfp_mask, nr_secs);
	if (!bio)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < nr_secs; i++) {
		page = vmalloc_to_page(kaddr);
		if (!page) {
			pblk_err(pblk, "could not map vmalloc bio\n");
			bio_put(bio);
			bio = ERR_PTR(-ENOMEM);
			goto out;
		}

		ret = bio_add_pc_page(dev->q, bio, page, PAGE_SIZE, 0);
		if (ret != PAGE_SIZE) {
			pblk_err(pblk, "could not add page to bio\n");
			bio_put(bio);
			bio = ERR_PTR(-ENOMEM);
			goto out;
		}

		kaddr += PAGE_SIZE;
	}

	bio->bi_end_io = pblk_bio_map_addr_endio;
out:
	return bio;
}