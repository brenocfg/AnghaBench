#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pqi_raid_path_request {int /*<<< orphan*/  request_id; int /*<<< orphan*/  error_index; } ;
struct pqi_raid_error_info {int dummy; } ;
struct pqi_iu_header {scalar_t__ iu_type; int /*<<< orphan*/  iu_length; } ;
struct pqi_io_request {struct pqi_iu_header* error_info; int /*<<< orphan*/ * context; int /*<<< orphan*/  io_complete_callback; struct pqi_raid_error_info* iu; int /*<<< orphan*/  index; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  sync_request_sem; TYPE_1__* pci_dev; int /*<<< orphan*/ * queue_groups; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 unsigned long NO_TIMEOUT ; 
 size_t PQI_DEFAULT_QUEUE_GROUP ; 
 size_t PQI_REQUEST_HEADER_LENGTH ; 
 scalar_t__ PQI_REQUEST_IU_RAID_PATH_IO ; 
 unsigned int PQI_SYNC_FLAGS_INTERRUPTABLE ; 
 int /*<<< orphan*/  RAID_PATH ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ down_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 unsigned long jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  memcpy (struct pqi_raid_error_info*,struct pqi_iu_header*,int) ; 
 int /*<<< orphan*/  memset (struct pqi_raid_error_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 struct pqi_io_request* pqi_alloc_io_request (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_busy (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_unbusy (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_free_io_request (struct pqi_io_request*) ; 
 int pqi_process_raid_io_error_synchronous (struct pqi_iu_header*) ; 
 int /*<<< orphan*/  pqi_raid_synchronous_complete ; 
 int /*<<< orphan*/  pqi_start_io (struct pqi_ctrl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pqi_io_request*) ; 
 int /*<<< orphan*/  pqi_wait_for_completion_io (struct pqi_ctrl_info*,int /*<<< orphan*/ *) ; 
 unsigned long pqi_wait_if_ctrl_blocked (struct pqi_ctrl_info*,unsigned long) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion_io_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pqi_submit_raid_request_synchronous(struct pqi_ctrl_info *ctrl_info,
	struct pqi_iu_header *request, unsigned int flags,
	struct pqi_raid_error_info *error_info, unsigned long timeout_msecs)
{
	int rc = 0;
	struct pqi_io_request *io_request;
	unsigned long start_jiffies;
	unsigned long msecs_blocked;
	size_t iu_length;
	DECLARE_COMPLETION_ONSTACK(wait);

	/*
	 * Note that specifying PQI_SYNC_FLAGS_INTERRUPTABLE and a timeout value
	 * are mutually exclusive.
	 */

	if (flags & PQI_SYNC_FLAGS_INTERRUPTABLE) {
		if (down_interruptible(&ctrl_info->sync_request_sem))
			return -ERESTARTSYS;
	} else {
		if (timeout_msecs == NO_TIMEOUT) {
			down(&ctrl_info->sync_request_sem);
		} else {
			start_jiffies = jiffies;
			if (down_timeout(&ctrl_info->sync_request_sem,
				msecs_to_jiffies(timeout_msecs)))
				return -ETIMEDOUT;
			msecs_blocked =
				jiffies_to_msecs(jiffies - start_jiffies);
			if (msecs_blocked >= timeout_msecs) {
				rc = -ETIMEDOUT;
				goto out;
			}
			timeout_msecs -= msecs_blocked;
		}
	}

	pqi_ctrl_busy(ctrl_info);
	timeout_msecs = pqi_wait_if_ctrl_blocked(ctrl_info, timeout_msecs);
	if (timeout_msecs == 0) {
		pqi_ctrl_unbusy(ctrl_info);
		rc = -ETIMEDOUT;
		goto out;
	}

	if (pqi_ctrl_offline(ctrl_info)) {
		pqi_ctrl_unbusy(ctrl_info);
		rc = -ENXIO;
		goto out;
	}

	io_request = pqi_alloc_io_request(ctrl_info);

	put_unaligned_le16(io_request->index,
		&(((struct pqi_raid_path_request *)request)->request_id));

	if (request->iu_type == PQI_REQUEST_IU_RAID_PATH_IO)
		((struct pqi_raid_path_request *)request)->error_index =
			((struct pqi_raid_path_request *)request)->request_id;

	iu_length = get_unaligned_le16(&request->iu_length) +
		PQI_REQUEST_HEADER_LENGTH;
	memcpy(io_request->iu, request, iu_length);

	io_request->io_complete_callback = pqi_raid_synchronous_complete;
	io_request->context = &wait;

	pqi_start_io(ctrl_info,
		&ctrl_info->queue_groups[PQI_DEFAULT_QUEUE_GROUP], RAID_PATH,
		io_request);

	pqi_ctrl_unbusy(ctrl_info);

	if (timeout_msecs == NO_TIMEOUT) {
		pqi_wait_for_completion_io(ctrl_info, &wait);
	} else {
		if (!wait_for_completion_io_timeout(&wait,
			msecs_to_jiffies(timeout_msecs))) {
			dev_warn(&ctrl_info->pci_dev->dev,
				"command timed out\n");
			rc = -ETIMEDOUT;
		}
	}

	if (error_info) {
		if (io_request->error_info)
			memcpy(error_info, io_request->error_info,
				sizeof(*error_info));
		else
			memset(error_info, 0, sizeof(*error_info));
	} else if (rc == 0 && io_request->error_info) {
		rc = pqi_process_raid_io_error_synchronous(
			io_request->error_info);
	}

	pqi_free_io_request(io_request);

out:
	up(&ctrl_info->sync_request_sem);

	return rc;
}