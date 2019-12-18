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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct htc_packet {int dummy; } ;
struct bus_request {int /*<<< orphan*/  list; struct htc_packet* packet; void* request; void* length; int /*<<< orphan*/ * buffer; void* address; } ;
struct ath6kl_sdio {int /*<<< orphan*/  wr_async_work; int /*<<< orphan*/  wr_async_lock; int /*<<< orphan*/  wr_asyncq; } ;
struct ath6kl {int /*<<< orphan*/  ath6kl_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct bus_request* ath6kl_sdio_alloc_busreq (struct ath6kl_sdio*) ; 
 struct ath6kl_sdio* ath6kl_sdio_priv (struct ath6kl*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_sdio_write_async(struct ath6kl *ar, u32 address, u8 *buffer,
				   u32 length, u32 request,
				   struct htc_packet *packet)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	struct bus_request *bus_req;

	bus_req = ath6kl_sdio_alloc_busreq(ar_sdio);

	if (WARN_ON_ONCE(!bus_req))
		return -ENOMEM;

	bus_req->address = address;
	bus_req->buffer = buffer;
	bus_req->length = length;
	bus_req->request = request;
	bus_req->packet = packet;

	spin_lock_bh(&ar_sdio->wr_async_lock);
	list_add_tail(&bus_req->list, &ar_sdio->wr_asyncq);
	spin_unlock_bh(&ar_sdio->wr_async_lock);
	queue_work(ar->ath6kl_wq, &ar_sdio->wr_async_work);

	return 0;
}