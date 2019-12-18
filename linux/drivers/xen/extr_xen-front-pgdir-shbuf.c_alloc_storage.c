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
struct xen_front_pgdir_shbuf {void* directory; void* grefs; int /*<<< orphan*/  num_grefs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  get_num_pages_dir (struct xen_front_pgdir_shbuf*) ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_storage(struct xen_front_pgdir_shbuf *buf)
{
	buf->grefs = kcalloc(buf->num_grefs, sizeof(*buf->grefs), GFP_KERNEL);
	if (!buf->grefs)
		return -ENOMEM;

	buf->directory = kcalloc(get_num_pages_dir(buf), PAGE_SIZE, GFP_KERNEL);
	if (!buf->directory)
		return -ENOMEM;

	return 0;
}