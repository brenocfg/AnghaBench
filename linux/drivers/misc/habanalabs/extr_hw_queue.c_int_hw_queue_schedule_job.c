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
typedef  int /*<<< orphan*/  u64 ;
struct hl_hw_queue {int pi; int int_queue_len; int /*<<< orphan*/  hw_queue_id; scalar_t__ kernel_address; } ;
struct hl_device {TYPE_3__* asic_funcs; struct hl_hw_queue* kernel_queues; } ;
struct hl_cs_job {size_t hw_queue_id; scalar_t__ user_cb; int /*<<< orphan*/  job_cb_size; TYPE_2__* cs; } ;
struct hl_bd {int /*<<< orphan*/  ptr; int /*<<< orphan*/  len; scalar_t__ ctl; } ;
typedef  int /*<<< orphan*/  bd ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_6__ {int /*<<< orphan*/  (* ring_doorbell ) (struct hl_device*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* pqe_write ) (struct hl_device*,int /*<<< orphan*/ *,struct hl_bd*) ;} ;
struct TYPE_5__ {TYPE_1__* ctx; } ;
struct TYPE_4__ {struct hl_device* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ *,struct hl_bd*) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void int_hw_queue_schedule_job(struct hl_cs_job *job)
{
	struct hl_device *hdev = job->cs->ctx->hdev;
	struct hl_hw_queue *q = &hdev->kernel_queues[job->hw_queue_id];
	struct hl_bd bd;
	__le64 *pi;

	bd.ctl = 0;
	bd.len = cpu_to_le32(job->job_cb_size);
	bd.ptr = cpu_to_le64((u64) (uintptr_t) job->user_cb);

	pi = (__le64 *) (uintptr_t) (q->kernel_address +
		((q->pi & (q->int_queue_len - 1)) * sizeof(bd)));

	q->pi++;
	q->pi &= ((q->int_queue_len << 1) - 1);

	hdev->asic_funcs->pqe_write(hdev, pi, &bd);

	hdev->asic_funcs->ring_doorbell(hdev, q->hw_queue_id, q->pi);
}