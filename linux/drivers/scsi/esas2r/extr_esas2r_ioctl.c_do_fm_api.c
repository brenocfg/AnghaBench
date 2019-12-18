#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct esas2r_flash_img {void* status; } ;
typedef  struct esas2r_flash_img u8 ;
struct esas2r_request {int /*<<< orphan*/  comp_cb; } ;
struct TYPE_5__ {scalar_t__ header_buff_phys; struct esas2r_flash_img* header_buff; struct esas2r_flash_img header; } ;
struct TYPE_6__ {struct esas2r_flash_img* cur_offset; void* get_phys_addr; } ;
struct esas2r_adapter {int /*<<< orphan*/  fm_api_mutex; TYPE_2__ firmware; TYPE_1__* pcid; scalar_t__ fm_api_command_done; int /*<<< orphan*/  fm_api_waiter; TYPE_3__ fm_api_sgc; struct esas2r_flash_img* save_offset; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  void* PGETPHYSADDR ;

/* Variables and functions */
 void* FI_STAT_BUSY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  complete_fm_api_req ; 
 struct esas2r_flash_img* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,struct esas2r_flash_img*,int /*<<< orphan*/ ) ; 
 struct esas2r_request* esas2r_alloc_request (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_debug (char*) ; 
 int /*<<< orphan*/  esas2r_fm_api (struct esas2r_adapter*,struct esas2r_flash_img*,struct esas2r_request*,TYPE_3__*) ; 
 int /*<<< orphan*/  esas2r_free_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 scalar_t__ get_physaddr_fm_api ; 
 scalar_t__ get_physaddr_fm_api_header ; 
 int /*<<< orphan*/  memcpy (struct esas2r_flash_img*,struct esas2r_flash_img*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void do_fm_api(struct esas2r_adapter *a, struct esas2r_flash_img *fi)
{
	struct esas2r_request *rq;

	if (mutex_lock_interruptible(&a->fm_api_mutex)) {
		fi->status = FI_STAT_BUSY;
		return;
	}

	rq = esas2r_alloc_request(a);
	if (rq == NULL) {
		fi->status = FI_STAT_BUSY;
		goto free_sem;
	}

	if (fi == &a->firmware.header) {
		a->firmware.header_buff = dma_alloc_coherent(&a->pcid->dev,
							     (size_t)sizeof(
								     struct
								     esas2r_flash_img),
							     (dma_addr_t *)&a->
							     firmware.
							     header_buff_phys,
							     GFP_KERNEL);

		if (a->firmware.header_buff == NULL) {
			esas2r_debug("failed to allocate header buffer!");
			fi->status = FI_STAT_BUSY;
			goto free_req;
		}

		memcpy(a->firmware.header_buff, fi,
		       sizeof(struct esas2r_flash_img));
		a->save_offset = a->firmware.header_buff;
		a->fm_api_sgc.get_phys_addr =
			(PGETPHYSADDR)get_physaddr_fm_api_header;
	} else {
		a->save_offset = (u8 *)fi;
		a->fm_api_sgc.get_phys_addr =
			(PGETPHYSADDR)get_physaddr_fm_api;
	}

	rq->comp_cb = complete_fm_api_req;
	a->fm_api_command_done = 0;
	a->fm_api_sgc.cur_offset = a->save_offset;

	if (!esas2r_fm_api(a, (struct esas2r_flash_img *)a->save_offset, rq,
			   &a->fm_api_sgc))
		goto all_done;

	/* Now wait around for it to complete. */
	while (!a->fm_api_command_done)
		wait_event_interruptible(a->fm_api_waiter,
					 a->fm_api_command_done);
all_done:
	if (fi == &a->firmware.header) {
		memcpy(fi, a->firmware.header_buff,
		       sizeof(struct esas2r_flash_img));

		dma_free_coherent(&a->pcid->dev,
				  (size_t)sizeof(struct esas2r_flash_img),
				  a->firmware.header_buff,
				  (dma_addr_t)a->firmware.header_buff_phys);
	}
free_req:
	esas2r_free_request(a, (struct esas2r_request *)rq);
free_sem:
	mutex_unlock(&a->fm_api_mutex);
	return;

}