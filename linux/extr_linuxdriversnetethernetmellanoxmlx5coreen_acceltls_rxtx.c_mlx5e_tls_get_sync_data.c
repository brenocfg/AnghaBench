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
typedef  void* u32 ;
struct tls_record_info {int /*<<< orphan*/ * frags; } ;
struct sync_info {int nr_frags; int /*<<< orphan*/ * frags; void* sync_len; int /*<<< orphan*/  rcd_sn; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mlx5e_tls_offload_context_tx {TYPE_1__ base; } ;
typedef  void* s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __skb_frag_ref (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tls_record_info* tls_get_record (TYPE_1__*,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_record_is_start_marker (struct tls_record_info*) ; 
 void* tls_record_start_seq (struct tls_record_info*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5e_tls_get_sync_data(struct mlx5e_tls_offload_context_tx *context,
				   u32 tcp_seq, struct sync_info *info)
{
	int remaining, i = 0, ret = -EINVAL;
	struct tls_record_info *record;
	unsigned long flags;
	s32 sync_size;

	spin_lock_irqsave(&context->base.lock, flags);
	record = tls_get_record(&context->base, tcp_seq, &info->rcd_sn);

	if (unlikely(!record))
		goto out;

	sync_size = tcp_seq - tls_record_start_seq(record);
	info->sync_len = sync_size;
	if (unlikely(sync_size < 0)) {
		if (tls_record_is_start_marker(record))
			goto done;

		goto out;
	}

	remaining = sync_size;
	while (remaining > 0) {
		info->frags[i] = record->frags[i];
		__skb_frag_ref(&info->frags[i]);
		remaining -= skb_frag_size(&info->frags[i]);

		if (remaining < 0)
			skb_frag_size_add(&info->frags[i], remaining);

		i++;
	}
	info->nr_frags = i;
done:
	ret = 0;
out:
	spin_unlock_irqrestore(&context->base.lock, flags);
	return ret;
}