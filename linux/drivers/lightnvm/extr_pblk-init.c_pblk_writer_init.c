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
struct pblk {int /*<<< orphan*/  wtimer; int /*<<< orphan*/  writer_ts; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,struct pblk*,char*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_write_timer_fn ; 
 int /*<<< orphan*/  pblk_write_ts ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_writer_init(struct pblk *pblk)
{
	pblk->writer_ts = kthread_create(pblk_write_ts, pblk, "pblk-writer-t");
	if (IS_ERR(pblk->writer_ts)) {
		int err = PTR_ERR(pblk->writer_ts);

		if (err != -EINTR)
			pblk_err(pblk, "could not allocate writer kthread (%d)\n",
					err);
		return err;
	}

	timer_setup(&pblk->wtimer, pblk_write_timer_fn, 0);
	mod_timer(&pblk->wtimer, jiffies + msecs_to_jiffies(100));

	return 0;
}