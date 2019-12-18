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
struct ath10k_sdio_bus_request {int /*<<< orphan*/  list; } ;
struct ath10k_sdio {int /*<<< orphan*/  lock; int /*<<< orphan*/  bus_req_freeq; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ath10k_sdio_bus_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_sdio_free_bus_req(struct ath10k *ar,
				     struct ath10k_sdio_bus_request *bus_req)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);

	memset(bus_req, 0, sizeof(*bus_req));

	spin_lock_bh(&ar_sdio->lock);
	list_add_tail(&bus_req->list, &ar_sdio->bus_req_freeq);
	spin_unlock_bh(&ar_sdio->lock);
}