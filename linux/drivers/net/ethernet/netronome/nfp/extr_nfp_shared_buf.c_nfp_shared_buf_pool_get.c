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
typedef  unsigned int u16 ;
struct nfp_shared_buf_pool_info_get {int /*<<< orphan*/  size; int /*<<< orphan*/  threshold_type; int /*<<< orphan*/  pool_type; } ;
struct nfp_shared_buf_pool_id {int /*<<< orphan*/  pool; int /*<<< orphan*/  shared_buf; } ;
struct nfp_pf {int dummy; } ;
struct devlink_sb_pool_info {unsigned int pool_type; unsigned int threshold_type; unsigned int size; unsigned int cell_size; } ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  get_data ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NFP_MBOX_POOL_GET ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int nfp_mbox_cmd (struct nfp_pf*,int /*<<< orphan*/ ,struct nfp_shared_buf_pool_id*,int,struct nfp_shared_buf_pool_info_get*,int) ; 
 unsigned int nfp_shared_buf_pool_unit (struct nfp_pf*,unsigned int) ; 

int nfp_shared_buf_pool_get(struct nfp_pf *pf, unsigned int sb, u16 pool_index,
			    struct devlink_sb_pool_info *pool_info)
{
	struct nfp_shared_buf_pool_info_get get_data;
	struct nfp_shared_buf_pool_id id = {
		.shared_buf	= cpu_to_le32(sb),
		.pool		= cpu_to_le32(pool_index),
	};
	unsigned int unit_size;
	int n;

	unit_size = nfp_shared_buf_pool_unit(pf, sb);
	if (!unit_size)
		return -EINVAL;

	n = nfp_mbox_cmd(pf, NFP_MBOX_POOL_GET, &id, sizeof(id),
			 &get_data, sizeof(get_data));
	if (n < 0)
		return n;
	if (n < sizeof(get_data))
		return -EIO;

	pool_info->pool_type = le32_to_cpu(get_data.pool_type);
	pool_info->threshold_type = le32_to_cpu(get_data.threshold_type);
	pool_info->size = le32_to_cpu(get_data.size) * unit_size;
	pool_info->cell_size = unit_size;

	return 0;
}