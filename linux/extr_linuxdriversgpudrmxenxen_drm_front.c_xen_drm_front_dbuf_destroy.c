#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_9__ {int /*<<< orphan*/  dbuf_cookie; } ;
struct TYPE_10__ {TYPE_3__ dbuf_destroy; } ;
struct xendispl_req {TYPE_4__ op; } ;
struct TYPE_8__ {int be_alloc; } ;
struct xen_drm_front_info {int /*<<< orphan*/  dbuf_list; int /*<<< orphan*/  io_lock; TYPE_2__ cfg; TYPE_1__* evt_pairs; } ;
struct TYPE_11__ {int /*<<< orphan*/  req_io_lock; } ;
struct TYPE_12__ {TYPE_5__ req; } ;
struct xen_drm_front_evtchnl {TYPE_6__ u; } ;
struct TYPE_7__ {struct xen_drm_front_evtchnl req; } ;

/* Variables and functions */
 int EIO ; 
 size_t GENERIC_OP_EVT_CHNL ; 
 int /*<<< orphan*/  XENDISPL_OP_DBUF_DESTROY ; 
 struct xendispl_req* be_prepare_req (struct xen_drm_front_evtchnl*,int /*<<< orphan*/ ) ; 
 int be_stream_do_io (struct xen_drm_front_evtchnl*,struct xendispl_req*) ; 
 int be_stream_wait_io (struct xen_drm_front_evtchnl*) ; 
 int /*<<< orphan*/  dbuf_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int xen_drm_front_dbuf_destroy(struct xen_drm_front_info *front_info,
				      u64 dbuf_cookie)
{
	struct xen_drm_front_evtchnl *evtchnl;
	struct xendispl_req *req;
	unsigned long flags;
	bool be_alloc;
	int ret;

	evtchnl = &front_info->evt_pairs[GENERIC_OP_EVT_CHNL].req;
	if (unlikely(!evtchnl))
		return -EIO;

	be_alloc = front_info->cfg.be_alloc;

	/*
	 * For the backend allocated buffer release references now, so backend
	 * can free the buffer.
	 */
	if (be_alloc)
		dbuf_free(&front_info->dbuf_list, dbuf_cookie);

	mutex_lock(&evtchnl->u.req.req_io_lock);

	spin_lock_irqsave(&front_info->io_lock, flags);
	req = be_prepare_req(evtchnl, XENDISPL_OP_DBUF_DESTROY);
	req->op.dbuf_destroy.dbuf_cookie = dbuf_cookie;

	ret = be_stream_do_io(evtchnl, req);
	spin_unlock_irqrestore(&front_info->io_lock, flags);

	if (ret == 0)
		ret = be_stream_wait_io(evtchnl);

	/*
	 * Do this regardless of communication status with the backend:
	 * if we cannot remove remote resources remove what we can locally.
	 */
	if (!be_alloc)
		dbuf_free(&front_info->dbuf_list, dbuf_cookie);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	return ret;
}