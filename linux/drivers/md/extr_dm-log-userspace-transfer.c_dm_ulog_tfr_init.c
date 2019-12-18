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
struct cn_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_PREALLOCED_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int cn_add_callback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cn_ulog_callback ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* prealloced_cn_msg ; 
 void* prealloced_ulog_tfr ; 
 int /*<<< orphan*/  receiving_list ; 
 int /*<<< orphan*/  ulog_cn_id ; 

int dm_ulog_tfr_init(void)
{
	int r;
	void *prealloced;

	INIT_LIST_HEAD(&receiving_list);

	prealloced = kmalloc(DM_ULOG_PREALLOCED_SIZE, GFP_KERNEL);
	if (!prealloced)
		return -ENOMEM;

	prealloced_cn_msg = prealloced;
	prealloced_ulog_tfr = prealloced + sizeof(struct cn_msg);

	r = cn_add_callback(&ulog_cn_id, "dmlogusr", cn_ulog_callback);
	if (r) {
		kfree(prealloced_cn_msg);
		return r;
	}

	return 0;
}