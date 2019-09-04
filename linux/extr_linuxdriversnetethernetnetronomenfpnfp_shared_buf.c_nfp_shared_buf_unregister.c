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
struct nfp_pf {unsigned int num_shared_bufs; TYPE_1__* shared_bufs; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_sb_unregister (struct devlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct devlink* priv_to_devlink (struct nfp_pf*) ; 

void nfp_shared_buf_unregister(struct nfp_pf *pf)
{
	struct devlink *devlink = priv_to_devlink(pf);
	unsigned int i;

	for (i = 0; i < pf->num_shared_bufs; i++)
		devlink_sb_unregister(devlink,
				      le32_to_cpu(pf->shared_bufs[i].id));
	kfree(pf->shared_bufs);
}