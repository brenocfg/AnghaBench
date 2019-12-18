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
struct muram_block {unsigned long start; unsigned long size; int /*<<< orphan*/  head; } ;
typedef  int /*<<< orphan*/  genpool_algo_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 unsigned long GENPOOL_OFFSET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cpm_muram_addr (unsigned long) ; 
 scalar_t__ cpm_muram_init () ; 
 unsigned long gen_pool_alloc_algo (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 struct muram_block* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  muram_block_list ; 
 int /*<<< orphan*/  muram_pool ; 

__attribute__((used)) static unsigned long cpm_muram_alloc_common(unsigned long size,
		genpool_algo_t algo, void *data)
{
	struct muram_block *entry;
	unsigned long start;

	if (!muram_pool && cpm_muram_init())
		goto out2;

	start = gen_pool_alloc_algo(muram_pool, size, algo, data);
	if (!start)
		goto out2;
	start = start - GENPOOL_OFFSET;
	memset_io(cpm_muram_addr(start), 0, size);
	entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry)
		goto out1;
	entry->start = start;
	entry->size = size;
	list_add(&entry->head, &muram_block_list);

	return start;
out1:
	gen_pool_free(muram_pool, start, size);
out2:
	return (unsigned long)-ENOMEM;
}