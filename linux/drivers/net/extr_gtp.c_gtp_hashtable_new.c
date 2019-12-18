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
struct hlist_head {int dummy; } ;
struct gtp_dev {int hash_size; int /*<<< orphan*/ * addr_hash; int /*<<< orphan*/ * tid_hash; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gtp_hashtable_new(struct gtp_dev *gtp, int hsize)
{
	int i;

	gtp->addr_hash = kmalloc_array(hsize, sizeof(struct hlist_head),
				       GFP_KERNEL);
	if (gtp->addr_hash == NULL)
		return -ENOMEM;

	gtp->tid_hash = kmalloc_array(hsize, sizeof(struct hlist_head),
				      GFP_KERNEL);
	if (gtp->tid_hash == NULL)
		goto err1;

	gtp->hash_size = hsize;

	for (i = 0; i < hsize; i++) {
		INIT_HLIST_HEAD(&gtp->addr_hash[i]);
		INIT_HLIST_HEAD(&gtp->tid_hash[i]);
	}
	return 0;
err1:
	kfree(gtp->addr_hash);
	return -ENOMEM;
}