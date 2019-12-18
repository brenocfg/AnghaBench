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
struct TYPE_2__ {int lsi_mask; int /*<<< orphan*/  isc; int /*<<< orphan*/  lsi_ptr; int /*<<< orphan*/  handler; } ;
struct airq_info {int summary_indicator_idx; int /*<<< orphan*/  aiv; TYPE_1__ airq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int AIRQ_IV_ALLOC ; 
 int AIRQ_IV_CACHELINE ; 
 int AIRQ_IV_PTR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_AIRQ_ISC ; 
 int /*<<< orphan*/  VIRTIO_IV_BITS ; 
 int /*<<< orphan*/  airq_iv_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  airq_iv_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_summary_indicator (struct airq_info*) ; 
 int /*<<< orphan*/  kfree (struct airq_info*) ; 
 struct airq_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int register_adapter_interrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_airq_handler ; 

__attribute__((used)) static struct airq_info *new_airq_info(int index)
{
	struct airq_info *info;
	int rc;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return NULL;
	rwlock_init(&info->lock);
	info->aiv = airq_iv_create(VIRTIO_IV_BITS, AIRQ_IV_ALLOC | AIRQ_IV_PTR
				   | AIRQ_IV_CACHELINE);
	if (!info->aiv) {
		kfree(info);
		return NULL;
	}
	info->airq.handler = virtio_airq_handler;
	info->summary_indicator_idx = index;
	info->airq.lsi_ptr = get_summary_indicator(info);
	info->airq.lsi_mask = 0xff;
	info->airq.isc = VIRTIO_AIRQ_ISC;
	rc = register_adapter_interrupt(&info->airq);
	if (rc) {
		airq_iv_release(info->aiv);
		kfree(info);
		return NULL;
	}
	return info;
}