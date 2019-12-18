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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct vnic_dev {int dummy; } ;
struct snic {int /*<<< orphan*/ * wq_lock; int /*<<< orphan*/ * wq; } ;
struct cq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
 int /*<<< orphan*/  snic_wq_cmpl_frame_send ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct snic* svnic_dev_priv (struct vnic_dev*) ; 
 int /*<<< orphan*/  svnic_wq_service (int /*<<< orphan*/ *,struct cq_desc*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snic_wq_cmpl_handler_cont(struct vnic_dev *vdev,
			  struct cq_desc *cq_desc,
			  u8 type,
			  u16 q_num,
			  u16 cmpl_idx,
			  void *opaque)
{
	struct snic *snic = svnic_dev_priv(vdev);
	unsigned long flags;

	SNIC_BUG_ON(q_num != 0);

	spin_lock_irqsave(&snic->wq_lock[q_num], flags);
	svnic_wq_service(&snic->wq[q_num],
			 cq_desc,
			 cmpl_idx,
			 snic_wq_cmpl_frame_send,
			 NULL);
	spin_unlock_irqrestore(&snic->wq_lock[q_num], flags);

	return 0;
}