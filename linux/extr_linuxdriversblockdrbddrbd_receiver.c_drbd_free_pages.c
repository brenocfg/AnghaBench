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
struct page {int dummy; } ;
struct drbd_device {int /*<<< orphan*/  pp_in_use; int /*<<< orphan*/  pp_in_use_by_net; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int DRBD_MAX_BIO_SIZE ; 
 int PAGE_SIZE ; 
 int atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 int drbd_minor_count ; 
 int /*<<< orphan*/  drbd_pp_lock ; 
 int /*<<< orphan*/  drbd_pp_pool ; 
 int drbd_pp_vacant ; 
 int /*<<< orphan*/  drbd_pp_wait ; 
 int /*<<< orphan*/  drbd_warn (struct drbd_device*,char*,char*,int) ; 
 int /*<<< orphan*/  page_chain_add (int /*<<< orphan*/ *,struct page*,struct page*) ; 
 int page_chain_free (struct page*) ; 
 struct page* page_chain_tail (struct page*,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_free_pages(struct drbd_device *device, struct page *page, int is_net)
{
	atomic_t *a = is_net ? &device->pp_in_use_by_net : &device->pp_in_use;
	int i;

	if (page == NULL)
		return;

	if (drbd_pp_vacant > (DRBD_MAX_BIO_SIZE/PAGE_SIZE) * drbd_minor_count)
		i = page_chain_free(page);
	else {
		struct page *tmp;
		tmp = page_chain_tail(page, &i);
		spin_lock(&drbd_pp_lock);
		page_chain_add(&drbd_pp_pool, page, tmp);
		drbd_pp_vacant += i;
		spin_unlock(&drbd_pp_lock);
	}
	i = atomic_sub_return(i, a);
	if (i < 0)
		drbd_warn(device, "ASSERTION FAILED: %s: %d < 0\n",
			is_net ? "pp_in_use_by_net" : "pp_in_use", i);
	wake_up(&drbd_pp_wait);
}