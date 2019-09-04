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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tidinfo ;
struct hfi1_tid_info {int tidcnt; int /*<<< orphan*/  tidlist; } ;
struct hfi1_filedata {int tid_used; int /*<<< orphan*/  tid_lock; struct hfi1_ctxtdata* uctxt; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  exp_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TID ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * memdup_user (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int unprogram_rcvarray (struct hfi1_filedata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hfi1_user_exp_rcv_clear(struct hfi1_filedata *fd,
			    struct hfi1_tid_info *tinfo)
{
	int ret = 0;
	struct hfi1_ctxtdata *uctxt = fd->uctxt;
	u32 *tidinfo;
	unsigned tididx;

	if (unlikely(tinfo->tidcnt > fd->tid_used))
		return -EINVAL;

	tidinfo = memdup_user(u64_to_user_ptr(tinfo->tidlist),
			      sizeof(tidinfo[0]) * tinfo->tidcnt);
	if (IS_ERR(tidinfo))
		return PTR_ERR(tidinfo);

	mutex_lock(&uctxt->exp_mutex);
	for (tididx = 0; tididx < tinfo->tidcnt; tididx++) {
		ret = unprogram_rcvarray(fd, tidinfo[tididx], NULL);
		if (ret) {
			hfi1_cdbg(TID, "Failed to unprogram rcv array %d",
				  ret);
			break;
		}
	}
	spin_lock(&fd->tid_lock);
	fd->tid_used -= tididx;
	spin_unlock(&fd->tid_lock);
	tinfo->tidcnt = tididx;
	mutex_unlock(&uctxt->exp_mutex);

	kfree(tidinfo);
	return ret;
}