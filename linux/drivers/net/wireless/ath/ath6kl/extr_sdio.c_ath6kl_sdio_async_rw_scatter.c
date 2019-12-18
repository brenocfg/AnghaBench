#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hif_scatter_req {int req; TYPE_1__* busrequest; int /*<<< orphan*/  scat_entries; int /*<<< orphan*/  len; } ;
struct ath6kl_sdio {int /*<<< orphan*/  wr_async_work; int /*<<< orphan*/  wr_async_lock; int /*<<< orphan*/  wr_asyncq; } ;
struct ath6kl {int /*<<< orphan*/  ath6kl_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_SCATTER ; 
 int EINVAL ; 
 int HIF_SYNCHRONOUS ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath6kl_sdio* ath6kl_sdio_priv (struct ath6kl*) ; 
 int ath6kl_sdio_scat_rw (struct ath6kl_sdio*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_sdio_async_rw_scatter(struct ath6kl *ar,
					struct hif_scatter_req *scat_req)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	u32 request = scat_req->req;
	int status = 0;

	if (!scat_req->len)
		return -EINVAL;

	ath6kl_dbg(ATH6KL_DBG_SCATTER,
		   "hif-scatter: total len: %d scatter entries: %d\n",
		   scat_req->len, scat_req->scat_entries);

	if (request & HIF_SYNCHRONOUS) {
		status = ath6kl_sdio_scat_rw(ar_sdio, scat_req->busrequest);
	} else {
		spin_lock_bh(&ar_sdio->wr_async_lock);
		list_add_tail(&scat_req->busrequest->list, &ar_sdio->wr_asyncq);
		spin_unlock_bh(&ar_sdio->wr_async_lock);
		queue_work(ar->ath6kl_wq, &ar_sdio->wr_async_work);
	}

	return status;
}