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
struct genwqe_mem {int addr; scalar_t__ size; } ;
struct genwqe_file {struct genwqe_dev* cd; } ;
struct genwqe_dev {int dummy; } ;
struct dma_mapping {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  genwqe_del_pin (struct genwqe_file*,struct dma_mapping*) ; 
 struct dma_mapping* genwqe_search_pin (struct genwqe_file*,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genwqe_user_vunmap (struct genwqe_dev*,struct dma_mapping*) ; 
 int /*<<< orphan*/  kfree (struct dma_mapping*) ; 
 unsigned long round_up (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genwqe_unpin_mem(struct genwqe_file *cfile, struct genwqe_mem *m)
{
	struct genwqe_dev *cd = cfile->cd;
	struct dma_mapping *dma_map;
	unsigned long map_addr;
	unsigned long map_size;

	if (m->addr == 0x0)
		return -EINVAL;

	map_addr = (m->addr & PAGE_MASK);
	map_size = round_up(m->size + (m->addr & ~PAGE_MASK), PAGE_SIZE);

	dma_map = genwqe_search_pin(cfile, map_addr, map_size, NULL);
	if (dma_map == NULL)
		return -ENOENT;

	genwqe_del_pin(cfile, dma_map);
	genwqe_user_vunmap(cd, dma_map);
	kfree(dma_map);
	return 0;
}