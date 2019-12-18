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

/* Variables and functions */
 int /*<<< orphan*/  cn_del_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prealloced_cn_msg ; 
 int /*<<< orphan*/  ulog_cn_id ; 

void dm_ulog_tfr_exit(void)
{
	cn_del_callback(&ulog_cn_id);
	kfree(prealloced_cn_msg);
}