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
typedef  void virtqueue ;
struct airq_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  aiv; } ;

/* Variables and functions */
 unsigned long airq_iv_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  airq_iv_free_bit (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ airq_iv_get_ptr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  airq_iv_set_ptr (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void drop_airq_indicator(struct virtqueue *vq, struct airq_info *info)
{
	unsigned long i, flags;

	write_lock_irqsave(&info->lock, flags);
	for (i = 0; i < airq_iv_end(info->aiv); i++) {
		if (vq == (void *)airq_iv_get_ptr(info->aiv, i)) {
			airq_iv_free_bit(info->aiv, i);
			airq_iv_set_ptr(info->aiv, i, 0);
			break;
		}
	}
	write_unlock_irqrestore(&info->lock, flags);
}