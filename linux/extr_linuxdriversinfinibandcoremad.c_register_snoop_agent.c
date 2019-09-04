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
struct ib_mad_snoop_private {int dummy; } ;
struct ib_mad_qp_info {int snoop_table_size; int /*<<< orphan*/  snoop_lock; int /*<<< orphan*/  snoop_count; struct ib_mad_snoop_private** snoop_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct ib_mad_snoop_private** krealloc (struct ib_mad_snoop_private**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int register_snoop_agent(struct ib_mad_qp_info *qp_info,
				struct ib_mad_snoop_private *mad_snoop_priv)
{
	struct ib_mad_snoop_private **new_snoop_table;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&qp_info->snoop_lock, flags);
	/* Check for empty slot in array. */
	for (i = 0; i < qp_info->snoop_table_size; i++)
		if (!qp_info->snoop_table[i])
			break;

	if (i == qp_info->snoop_table_size) {
		/* Grow table. */
		new_snoop_table = krealloc(qp_info->snoop_table,
					   sizeof mad_snoop_priv *
					   (qp_info->snoop_table_size + 1),
					   GFP_ATOMIC);
		if (!new_snoop_table) {
			i = -ENOMEM;
			goto out;
		}

		qp_info->snoop_table = new_snoop_table;
		qp_info->snoop_table_size++;
	}
	qp_info->snoop_table[i] = mad_snoop_priv;
	atomic_inc(&qp_info->snoop_count);
out:
	spin_unlock_irqrestore(&qp_info->snoop_lock, flags);
	return i;
}