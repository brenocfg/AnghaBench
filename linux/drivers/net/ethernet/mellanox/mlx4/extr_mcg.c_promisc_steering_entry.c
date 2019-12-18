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
typedef  int u8 ;
typedef  int u32 ;
struct mlx4_mgm {int /*<<< orphan*/ * qp; int /*<<< orphan*/  members_count; } ;
struct TYPE_2__ {int num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {struct mlx4_mgm* buf; } ;
typedef  enum mlx4_steer_type { ____Placeholder_mlx4_steer_type } mlx4_steer_type ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int MGM_QPN_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_promisc_qp (struct mlx4_dev*,int,int,int) ; 
 scalar_t__ mlx4_READ_ENTRY (struct mlx4_dev*,unsigned int,struct mlx4_cmd_mailbox*) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

__attribute__((used)) static bool promisc_steering_entry(struct mlx4_dev *dev, u8 port,
				   enum mlx4_steer_type steer,
				   unsigned int index, u32 tqpn,
				   u32 *members_count)
{
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_mgm *mgm;
	u32 m_count;
	bool ret = false;
	int i;

	if (port < 1 || port > dev->caps.num_ports)
		return false;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return false;
	mgm = mailbox->buf;

	if (mlx4_READ_ENTRY(dev, index, mailbox))
		goto out;
	m_count = be32_to_cpu(mgm->members_count) & 0xffffff;
	if (members_count)
		*members_count = m_count;

	for (i = 0;  i < m_count; i++) {
		u32 qpn = be32_to_cpu(mgm->qp[i]) & MGM_QPN_MASK;
		if (!get_promisc_qp(dev, port, steer, qpn) && qpn != tqpn) {
			/* the qp is not promisc, the entry can't be removed */
			goto out;
		}
	}
	ret = true;
out:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return ret;
}