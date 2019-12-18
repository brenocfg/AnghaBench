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
struct msc {int burst_len; scalar_t__ reg_base; int /*<<< orphan*/  iter_list; int /*<<< orphan*/  win_list; int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  mode; int /*<<< orphan*/  user_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MSC_LEN ; 
 int /*<<< orphan*/  MSC_MODE_MULTI ; 
 scalar_t__ REG_MSU_MSC0CTL ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_th_msc_init(struct msc *msc)
{
	atomic_set(&msc->user_count, -1);

	msc->mode = MSC_MODE_MULTI;
	mutex_init(&msc->buf_mutex);
	INIT_LIST_HEAD(&msc->win_list);
	INIT_LIST_HEAD(&msc->iter_list);

	msc->burst_len =
		(ioread32(msc->reg_base + REG_MSU_MSC0CTL) & MSC_LEN) >>
		__ffs(MSC_LEN);

	return 0;
}