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
typedef  scalar_t__ u8 ;
struct esas2r_request {int /*<<< orphan*/  req_stat; int /*<<< orphan*/ * interrupt_cb; scalar_t__ interrupt_cx; } ;
struct esas2r_flash_img {int /*<<< orphan*/  driver_error; scalar_t__ status; } ;
struct esas2r_flash_context {int /*<<< orphan*/  scratch; struct esas2r_flash_img* fi; } ;
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_FLASH_LOCK ; 
 scalar_t__ FI_STAT_IMG_VER ; 
 int /*<<< orphan*/  FM_BUF_SZ ; 
 int /*<<< orphan*/  RS_SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_enable_heartbeat (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool complete_fmapi_req(struct esas2r_adapter *a,
			       struct esas2r_request *rq, u8 fi_stat)
{
	struct esas2r_flash_context *fc =
		(struct esas2r_flash_context *)rq->interrupt_cx;
	struct esas2r_flash_img *fi = fc->fi;

	fi->status = fi_stat;
	fi->driver_error = rq->req_stat;
	rq->interrupt_cb = NULL;
	rq->req_stat = RS_SUCCESS;

	if (fi_stat != FI_STAT_IMG_VER)
		memset(fc->scratch, 0, FM_BUF_SZ);

	esas2r_enable_heartbeat(a);
	clear_bit(AF_FLASH_LOCK, &a->flags);
	return false;
}