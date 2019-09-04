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
struct cfv_info {int /*<<< orphan*/  genpool; } ;
struct buf_info {int /*<<< orphan*/  size; scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buf_info*) ; 

__attribute__((used)) static void free_buf_info(struct cfv_info *cfv, struct buf_info *buf_info)
{
	if (!buf_info)
		return;
	gen_pool_free(cfv->genpool, (unsigned long) buf_info->vaddr,
		      buf_info->size);
	kfree(buf_info);
}