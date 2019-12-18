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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int* pkey_table_len; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int dummy; } ;

/* Variables and functions */
 int query_pkey_block (struct mlx4_dev*,size_t,int,int /*<<< orphan*/ *,struct mlx4_cmd_mailbox*,struct mlx4_cmd_mailbox*) ; 

__attribute__((used)) static int get_full_pkey_table(struct mlx4_dev *dev, u8 port, u16 *table,
			       struct mlx4_cmd_mailbox *inbox,
			       struct mlx4_cmd_mailbox *outbox)
{
	int i;
	int err;

	for (i = 0; i < dev->caps.pkey_table_len[port]; i += 32) {
		err = query_pkey_block(dev, port, i, table + i, inbox, outbox);
		if (err)
			return err;
	}

	return 0;
}