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
typedef  int /*<<< orphan*/  u16 ;
struct nfp_pf {int dummy; } ;
struct devlink_sb_pool_info {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct nfp_pf* devlink_priv (struct devlink*) ; 
 int nfp_shared_buf_pool_get (struct nfp_pf*,unsigned int,int /*<<< orphan*/ ,struct devlink_sb_pool_info*) ; 

__attribute__((used)) static int
nfp_devlink_sb_pool_get(struct devlink *devlink, unsigned int sb_index,
			u16 pool_index, struct devlink_sb_pool_info *pool_info)
{
	struct nfp_pf *pf = devlink_priv(devlink);

	return nfp_shared_buf_pool_get(pf, sb_index, pool_index, pool_info);
}