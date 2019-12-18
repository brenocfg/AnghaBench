#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct esas2r_request {scalar_t__ req_stat; int /*<<< orphan*/  (* interrupt_cb ) (struct esas2r_adapter*,struct esas2r_request*) ;scalar_t__ interrupt_cx; TYPE_2__* vrq; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cur_offset; } ;
struct esas2r_flash_context {int /*<<< orphan*/  (* interrupt_cb ) (struct esas2r_adapter*,struct esas2r_request*) ;TYPE_1__ sgc; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_vda_flash_req {int sub_func; } ;
struct TYPE_4__ {struct atto_vda_flash_req flash; } ;

/* Variables and functions */
 scalar_t__ RS_PENDING ; 
 scalar_t__ RS_SUCCESS ; 
#define  VDA_FLASH_BEGINW 129 
 int VDA_FLASH_COMMIT ; 
#define  VDA_FLASH_WRITE 128 
 int /*<<< orphan*/  stub1 (struct esas2r_adapter*,struct esas2r_request*) ; 

__attribute__((used)) static void esas2r_fmapi_callback(struct esas2r_adapter *a,
				  struct esas2r_request *rq)
{
	struct atto_vda_flash_req *vrq = &rq->vrq->flash;
	struct esas2r_flash_context *fc =
		(struct esas2r_flash_context *)rq->interrupt_cx;

	if (rq->req_stat == RS_SUCCESS) {
		/* Last request was successful.  See what to do now. */
		switch (vrq->sub_func) {
		case VDA_FLASH_BEGINW:
			if (fc->sgc.cur_offset == NULL)
				goto commit;

			vrq->sub_func = VDA_FLASH_WRITE;
			rq->req_stat = RS_PENDING;
			break;

		case VDA_FLASH_WRITE:
commit:
			vrq->sub_func = VDA_FLASH_COMMIT;
			rq->req_stat = RS_PENDING;
			rq->interrupt_cb = fc->interrupt_cb;
			break;

		default:
			break;
		}
	}

	if (rq->req_stat != RS_PENDING)
		/*
		 * All done. call the real callback to complete the FM API
		 * request.  We should only get here if a BEGINW or WRITE
		 * operation failed.
		 */
		(*fc->interrupt_cb)(a, rq);
}