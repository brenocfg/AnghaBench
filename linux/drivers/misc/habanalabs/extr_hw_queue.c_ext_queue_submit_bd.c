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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_hw_queue {int /*<<< orphan*/  pi; int /*<<< orphan*/  hw_queue_id; scalar_t__ kernel_address; } ;
struct hl_device {TYPE_1__* asic_funcs; } ;
struct hl_bd {int /*<<< orphan*/  ptr; void* len; void* ctl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ring_doorbell ) (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_pi_2_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_queue_inc_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext_queue_submit_bd(struct hl_device *hdev, struct hl_hw_queue *q,
				u32 ctl, u32 len, u64 ptr)
{
	struct hl_bd *bd;

	bd = (struct hl_bd *) (uintptr_t) q->kernel_address;
	bd += hl_pi_2_offset(q->pi);
	bd->ctl = cpu_to_le32(ctl);
	bd->len = cpu_to_le32(len);
	bd->ptr = cpu_to_le64(ptr);

	q->pi = hl_queue_inc_ptr(q->pi);
	hdev->asic_funcs->ring_doorbell(hdev, q->hw_queue_id, q->pi);
}