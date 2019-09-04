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
typedef  unsigned long long u64 ;
struct TYPE_2__ {int /*<<< orphan*/  res_id; } ;
struct res_mtt {TYPE_1__ com; } ;
struct mlx4_vhcr {int in_modifier; } ;
struct mlx4_mtt {scalar_t__ page_shift; scalar_t__ order; scalar_t__ offset; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/ * buf; } ;
struct mlx4_cmd_info {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  RES_MTT ; 
 int __mlx4_write_mtt (struct mlx4_dev*,struct mlx4_mtt*,unsigned long long,int,unsigned long long*) ; 
 unsigned long long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int get_containing_mtt (struct mlx4_dev*,int,int,int,struct res_mtt**) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_WRITE_MTT_wrapper(struct mlx4_dev *dev, int slave,
			   struct mlx4_vhcr *vhcr,
			   struct mlx4_cmd_mailbox *inbox,
			   struct mlx4_cmd_mailbox *outbox,
			   struct mlx4_cmd_info *cmd)
{
	struct mlx4_mtt mtt;
	__be64 *page_list = inbox->buf;
	u64 *pg_list = (u64 *)page_list;
	int i;
	struct res_mtt *rmtt = NULL;
	int start = be64_to_cpu(page_list[0]);
	int npages = vhcr->in_modifier;
	int err;

	err = get_containing_mtt(dev, slave, start, npages, &rmtt);
	if (err)
		return err;

	/* Call the SW implementation of write_mtt:
	 * - Prepare a dummy mtt struct
	 * - Translate inbox contents to simple addresses in host endianness */
	mtt.offset = 0;  /* TBD this is broken but I don't handle it since
			    we don't really use it */
	mtt.order = 0;
	mtt.page_shift = 0;
	for (i = 0; i < npages; ++i)
		pg_list[i + 2] = (be64_to_cpu(page_list[i + 2]) & ~1ULL);

	err = __mlx4_write_mtt(dev, &mtt, be64_to_cpu(page_list[0]), npages,
			       ((u64 *)page_list + 2));

	if (rmtt)
		put_res(dev, slave, rmtt->com.res_id, RES_MTT);

	return err;
}