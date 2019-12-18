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
struct bus_request {void* packet; int /*<<< orphan*/  request; int /*<<< orphan*/  length; int /*<<< orphan*/  buffer; int /*<<< orphan*/  address; scalar_t__ scat_req; } ;
struct ath6kl_sdio {int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_hif_rw_comp_handler (void*,int) ; 
 int /*<<< orphan*/  ath6kl_sdio_free_bus_req (struct ath6kl_sdio*,struct bus_request*) ; 
 int ath6kl_sdio_read_write_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_sdio_scat_rw (struct ath6kl_sdio*,struct bus_request*) ; 

__attribute__((used)) static void __ath6kl_sdio_write_async(struct ath6kl_sdio *ar_sdio,
				      struct bus_request *req)
{
	if (req->scat_req) {
		ath6kl_sdio_scat_rw(ar_sdio, req);
	} else {
		void *context;
		int status;

		status = ath6kl_sdio_read_write_sync(ar_sdio->ar, req->address,
						     req->buffer, req->length,
						     req->request);
		context = req->packet;
		ath6kl_sdio_free_bus_req(ar_sdio, req);
		ath6kl_hif_rw_comp_handler(context, status);
	}
}