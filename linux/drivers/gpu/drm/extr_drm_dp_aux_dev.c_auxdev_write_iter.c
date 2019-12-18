#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct kiocb {scalar_t__ ki_pos; TYPE_1__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct drm_dp_aux_dev {int /*<<< orphan*/  usecount; TYPE_2__* aux; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {scalar_t__ is_remote; } ;
struct TYPE_4__ {struct drm_dp_aux_dev* private_data; } ;

/* Variables and functions */
 scalar_t__ AUX_MAX_OFFSET ; 
 int DP_AUX_MAX_PAYLOAD_BYTES ; 
 scalar_t__ EFAULT ; 
 scalar_t__ ENODEV ; 
 scalar_t__ ERESTARTSYS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_from_iter_full (int /*<<< orphan*/ *,scalar_t__,struct iov_iter*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ drm_dp_dpcd_write (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ drm_dp_mst_dpcd_write (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t auxdev_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct drm_dp_aux_dev *aux_dev = iocb->ki_filp->private_data;
	loff_t pos = iocb->ki_pos;
	ssize_t res = 0;

	if (!atomic_inc_not_zero(&aux_dev->usecount))
		return -ENODEV;

	iov_iter_truncate(from, AUX_MAX_OFFSET - pos);

	while (iov_iter_count(from)) {
		uint8_t buf[DP_AUX_MAX_PAYLOAD_BYTES];
		ssize_t todo = min(iov_iter_count(from), sizeof(buf));

		if (signal_pending(current)) {
			res = -ERESTARTSYS;
			break;
		}

		if (!copy_from_iter_full(buf, todo, from)) {
			res = -EFAULT;
			break;
		}

		if (aux_dev->aux->is_remote)
			res = drm_dp_mst_dpcd_write(aux_dev->aux, pos, buf,
						    todo);
		else
			res = drm_dp_dpcd_write(aux_dev->aux, pos, buf, todo);

		if (res <= 0)
			break;

		pos += res;
	}

	if (pos != iocb->ki_pos)
		res = pos - iocb->ki_pos;
	iocb->ki_pos = pos;

	if (atomic_dec_and_test(&aux_dev->usecount))
		wake_up_var(&aux_dev->usecount);

	return res;
}