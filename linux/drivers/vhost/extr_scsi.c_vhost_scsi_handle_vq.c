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
typedef  int /*<<< orphan*/  vc ;
typedef  int /*<<< orphan*/  v_req_pi ;
typedef  int /*<<< orphan*/  v_req ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct virtio_scsi_cmd_resp {int dummy; } ;
struct virtio_scsi_cmd_req_pi {int* lun; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  task_attr; int /*<<< orphan*/  tag; scalar_t__ pi_bytesin; scalar_t__ pi_bytesout; } ;
struct virtio_scsi_cmd_req {int* lun; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  task_attr; int /*<<< orphan*/  tag; scalar_t__ pi_bytesin; scalar_t__ pi_bytesout; } ;
struct vhost_virtqueue {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * iov; struct vhost_scsi_tpg** private_data; } ;
struct vhost_scsi_tpg {int dummy; } ;
struct iov_iter {int dummy; } ;
struct vhost_scsi_ctx {int rsp_size; int req_size; int* lunp; int* target; scalar_t__ out_size; scalar_t__ in_size; size_t out; int /*<<< orphan*/  head; int /*<<< orphan*/  in; struct iov_iter out_iter; struct virtio_scsi_cmd_req_pi* req; } ;
struct vhost_scsi_cmd {int /*<<< orphan*/  work; int /*<<< orphan*/  tvc_vq_desc; int /*<<< orphan*/  tvc_se_cmd; int /*<<< orphan*/  tvc_lun; int /*<<< orphan*/ * tvc_cdb; int /*<<< orphan*/  tvc_in_iovs; int /*<<< orphan*/  tvc_resp_iov; struct vhost_virtqueue* tvc_vq; struct vhost_scsi* tvc_vhost; } ;
struct vhost_scsi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_NONE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct vhost_scsi_cmd*) ; 
 int /*<<< orphan*/  PTR_ERR (struct vhost_scsi_cmd*) ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ VHOST_SCSI_MAX_CDB_SIZE ; 
 int /*<<< orphan*/  VIRTIO_SCSI_F_T10_PI ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,int) ; 
 int /*<<< orphan*/  iov_iter_init (struct iov_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct vhost_scsi_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct vhost_scsi_cmd*,scalar_t__,...) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_command_size (void*) ; 
 scalar_t__ unlikely (int) ; 
 int vhost32_to_cpu (struct vhost_virtqueue*,scalar_t__) ; 
 int /*<<< orphan*/  vhost64_to_cpu (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_disable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_exceeds_weight (struct vhost_virtqueue*,int,int /*<<< orphan*/ ) ; 
 int vhost_has_feature (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 int vhost_scsi_chk_size (struct vhost_virtqueue*,struct vhost_scsi_ctx*) ; 
 int vhost_scsi_get_desc (struct vhost_scsi*,struct vhost_virtqueue*,struct vhost_scsi_ctx*) ; 
 int vhost_scsi_get_req (struct vhost_virtqueue*,struct vhost_scsi_ctx*,struct vhost_scsi_tpg**) ; 
 struct vhost_scsi_cmd* vhost_scsi_get_tag (struct vhost_virtqueue*,struct vhost_scsi_tpg*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int vhost_scsi_mapal (struct vhost_scsi_cmd*,int,struct iov_iter*,scalar_t__,struct iov_iter*) ; 
 int /*<<< orphan*/  vhost_scsi_release_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_scsi_send_bad_target (struct vhost_scsi*,struct vhost_virtqueue*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vhost_scsi_submission_work ; 
 int /*<<< orphan*/  vhost_scsi_workqueue ; 
 int /*<<< orphan*/  vq_err (struct vhost_virtqueue*,char*,...) ; 

__attribute__((used)) static void
vhost_scsi_handle_vq(struct vhost_scsi *vs, struct vhost_virtqueue *vq)
{
	struct vhost_scsi_tpg **vs_tpg, *tpg;
	struct virtio_scsi_cmd_req v_req;
	struct virtio_scsi_cmd_req_pi v_req_pi;
	struct vhost_scsi_ctx vc;
	struct vhost_scsi_cmd *cmd;
	struct iov_iter in_iter, prot_iter, data_iter;
	u64 tag;
	u32 exp_data_len, data_direction;
	int ret, prot_bytes, c = 0;
	u16 lun;
	u8 task_attr;
	bool t10_pi = vhost_has_feature(vq, VIRTIO_SCSI_F_T10_PI);
	void *cdb;

	mutex_lock(&vq->mutex);
	/*
	 * We can handle the vq only after the endpoint is setup by calling the
	 * VHOST_SCSI_SET_ENDPOINT ioctl.
	 */
	vs_tpg = vq->private_data;
	if (!vs_tpg)
		goto out;

	memset(&vc, 0, sizeof(vc));
	vc.rsp_size = sizeof(struct virtio_scsi_cmd_resp);

	vhost_disable_notify(&vs->dev, vq);

	do {
		ret = vhost_scsi_get_desc(vs, vq, &vc);
		if (ret)
			goto err;

		/*
		 * Setup pointers and values based upon different virtio-scsi
		 * request header if T10_PI is enabled in KVM guest.
		 */
		if (t10_pi) {
			vc.req = &v_req_pi;
			vc.req_size = sizeof(v_req_pi);
			vc.lunp = &v_req_pi.lun[0];
			vc.target = &v_req_pi.lun[1];
		} else {
			vc.req = &v_req;
			vc.req_size = sizeof(v_req);
			vc.lunp = &v_req.lun[0];
			vc.target = &v_req.lun[1];
		}

		/*
		 * Validate the size of request and response buffers.
		 * Check for a sane response buffer so we can report
		 * early errors back to the guest.
		 */
		ret = vhost_scsi_chk_size(vq, &vc);
		if (ret)
			goto err;

		ret = vhost_scsi_get_req(vq, &vc, &tpg);
		if (ret)
			goto err;

		ret = -EIO;	/* bad target on any error from here on */

		/*
		 * Determine data_direction by calculating the total outgoing
		 * iovec sizes + incoming iovec sizes vs. virtio-scsi request +
		 * response headers respectively.
		 *
		 * For DMA_TO_DEVICE this is out_iter, which is already pointing
		 * to the right place.
		 *
		 * For DMA_FROM_DEVICE, the iovec will be just past the end
		 * of the virtio-scsi response header in either the same
		 * or immediately following iovec.
		 *
		 * Any associated T10_PI bytes for the outgoing / incoming
		 * payloads are included in calculation of exp_data_len here.
		 */
		prot_bytes = 0;

		if (vc.out_size > vc.req_size) {
			data_direction = DMA_TO_DEVICE;
			exp_data_len = vc.out_size - vc.req_size;
			data_iter = vc.out_iter;
		} else if (vc.in_size > vc.rsp_size) {
			data_direction = DMA_FROM_DEVICE;
			exp_data_len = vc.in_size - vc.rsp_size;

			iov_iter_init(&in_iter, READ, &vq->iov[vc.out], vc.in,
				      vc.rsp_size + exp_data_len);
			iov_iter_advance(&in_iter, vc.rsp_size);
			data_iter = in_iter;
		} else {
			data_direction = DMA_NONE;
			exp_data_len = 0;
		}
		/*
		 * If T10_PI header + payload is present, setup prot_iter values
		 * and recalculate data_iter for vhost_scsi_mapal() mapping to
		 * host scatterlists via get_user_pages_fast().
		 */
		if (t10_pi) {
			if (v_req_pi.pi_bytesout) {
				if (data_direction != DMA_TO_DEVICE) {
					vq_err(vq, "Received non zero pi_bytesout,"
						" but wrong data_direction\n");
					goto err;
				}
				prot_bytes = vhost32_to_cpu(vq, v_req_pi.pi_bytesout);
			} else if (v_req_pi.pi_bytesin) {
				if (data_direction != DMA_FROM_DEVICE) {
					vq_err(vq, "Received non zero pi_bytesin,"
						" but wrong data_direction\n");
					goto err;
				}
				prot_bytes = vhost32_to_cpu(vq, v_req_pi.pi_bytesin);
			}
			/*
			 * Set prot_iter to data_iter and truncate it to
			 * prot_bytes, and advance data_iter past any
			 * preceeding prot_bytes that may be present.
			 *
			 * Also fix up the exp_data_len to reflect only the
			 * actual data payload length.
			 */
			if (prot_bytes) {
				exp_data_len -= prot_bytes;
				prot_iter = data_iter;
				iov_iter_truncate(&prot_iter, prot_bytes);
				iov_iter_advance(&data_iter, prot_bytes);
			}
			tag = vhost64_to_cpu(vq, v_req_pi.tag);
			task_attr = v_req_pi.task_attr;
			cdb = &v_req_pi.cdb[0];
			lun = ((v_req_pi.lun[2] << 8) | v_req_pi.lun[3]) & 0x3FFF;
		} else {
			tag = vhost64_to_cpu(vq, v_req.tag);
			task_attr = v_req.task_attr;
			cdb = &v_req.cdb[0];
			lun = ((v_req.lun[2] << 8) | v_req.lun[3]) & 0x3FFF;
		}
		/*
		 * Check that the received CDB size does not exceeded our
		 * hardcoded max for vhost-scsi, then get a pre-allocated
		 * cmd descriptor for the new virtio-scsi tag.
		 *
		 * TODO what if cdb was too small for varlen cdb header?
		 */
		if (unlikely(scsi_command_size(cdb) > VHOST_SCSI_MAX_CDB_SIZE)) {
			vq_err(vq, "Received SCSI CDB with command_size: %d that"
				" exceeds SCSI_MAX_VARLEN_CDB_SIZE: %d\n",
				scsi_command_size(cdb), VHOST_SCSI_MAX_CDB_SIZE);
				goto err;
		}
		cmd = vhost_scsi_get_tag(vq, tpg, cdb, tag, lun, task_attr,
					 exp_data_len + prot_bytes,
					 data_direction);
		if (IS_ERR(cmd)) {
			vq_err(vq, "vhost_scsi_get_tag failed %ld\n",
			       PTR_ERR(cmd));
			goto err;
		}
		cmd->tvc_vhost = vs;
		cmd->tvc_vq = vq;
		cmd->tvc_resp_iov = vq->iov[vc.out];
		cmd->tvc_in_iovs = vc.in;

		pr_debug("vhost_scsi got command opcode: %#02x, lun: %d\n",
			 cmd->tvc_cdb[0], cmd->tvc_lun);
		pr_debug("cmd: %p exp_data_len: %d, prot_bytes: %d data_direction:"
			 " %d\n", cmd, exp_data_len, prot_bytes, data_direction);

		if (data_direction != DMA_NONE) {
			if (unlikely(vhost_scsi_mapal(cmd, prot_bytes,
						      &prot_iter, exp_data_len,
						      &data_iter))) {
				vq_err(vq, "Failed to map iov to sgl\n");
				vhost_scsi_release_cmd(&cmd->tvc_se_cmd);
				goto err;
			}
		}
		/*
		 * Save the descriptor from vhost_get_vq_desc() to be used to
		 * complete the virtio-scsi request in TCM callback context via
		 * vhost_scsi_queue_data_in() and vhost_scsi_queue_status()
		 */
		cmd->tvc_vq_desc = vc.head;
		/*
		 * Dispatch cmd descriptor for cmwq execution in process
		 * context provided by vhost_scsi_workqueue.  This also ensures
		 * cmd is executed on the same kworker CPU as this vhost
		 * thread to gain positive L2 cache locality effects.
		 */
		INIT_WORK(&cmd->work, vhost_scsi_submission_work);
		queue_work(vhost_scsi_workqueue, &cmd->work);
		ret = 0;
err:
		/*
		 * ENXIO:  No more requests, or read error, wait for next kick
		 * EINVAL: Invalid response buffer, drop the request
		 * EIO:    Respond with bad target
		 * EAGAIN: Pending request
		 */
		if (ret == -ENXIO)
			break;
		else if (ret == -EIO)
			vhost_scsi_send_bad_target(vs, vq, vc.head, vc.out);
	} while (likely(!vhost_exceeds_weight(vq, ++c, 0)));
out:
	mutex_unlock(&vq->mutex);
}