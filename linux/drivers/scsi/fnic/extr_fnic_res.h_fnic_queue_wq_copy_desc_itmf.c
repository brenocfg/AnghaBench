#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct vnic_wq_copy {int dummy; } ;
struct TYPE_9__ {void* e_d_tov; void* r_a_tov; int /*<<< orphan*/  d_id; scalar_t__ _resvd1; int /*<<< orphan*/  lun; scalar_t__ _resvd; void* t_tag; void* tm_req; void* lunmap_id; } ;
struct TYPE_10__ {TYPE_4__ itmf; } ;
struct TYPE_6__ {void* req_id; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct TYPE_8__ {TYPE_2__ tag; scalar_t__ _resvd; scalar_t__ status; int /*<<< orphan*/  type; } ;
struct fcpio_host_req {TYPE_5__ u; TYPE_3__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCPIO_ITMF ; 
 int /*<<< orphan*/  LUN_ADDRESS ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fcpio_host_req* vnic_wq_copy_next_desc (struct vnic_wq_copy*) ; 
 int /*<<< orphan*/  vnic_wq_copy_post (struct vnic_wq_copy*) ; 

__attribute__((used)) static inline void fnic_queue_wq_copy_desc_itmf(struct vnic_wq_copy *wq,
						u32 req_id, u32 lunmap_id,
						u32 tm_req, u32 tm_id, u8 *lun,
						u32 d_id, u32 r_a_tov,
						u32 e_d_tov)
{
	struct fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_ITMF;     /* enum fcpio_type */
	desc->hdr.status = 0;            /* header status entry */
	desc->hdr._resvd = 0;            /* reserved */
	desc->hdr.tag.u.req_id = req_id; /* id for this request */

	desc->u.itmf.lunmap_id = lunmap_id; /* index into lunmap table */
	desc->u.itmf.tm_req = tm_req;       /* SCSI Task Management request */
	desc->u.itmf.t_tag = tm_id;         /* tag of fcpio to be aborted */
	desc->u.itmf._resvd = 0;
	memcpy(desc->u.itmf.lun, lun, LUN_ADDRESS);  /* LUN address */
	desc->u.itmf._resvd1 = 0;
	hton24(desc->u.itmf.d_id, d_id);    /* FC vNIC only: Target D_ID */
	desc->u.itmf.r_a_tov = r_a_tov;     /* FC vNIC only: R_A_TOV in msec */
	desc->u.itmf.e_d_tov = e_d_tov;     /* FC vNIC only: E_D_TOV in msec */

	vnic_wq_copy_post(wq);
}