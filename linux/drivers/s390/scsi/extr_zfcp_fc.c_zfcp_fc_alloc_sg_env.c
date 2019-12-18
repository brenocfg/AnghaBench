#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  req; } ;
struct TYPE_4__ {TYPE_1__ gpn_ft; } ;
struct zfcp_fc_req {TYPE_2__ u; int /*<<< orphan*/  sg_req; int /*<<< orphan*/  sg_rsp; } ;
struct zfcp_fc_gpn_ft_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct zfcp_fc_req*) ; 
 struct zfcp_fc_req* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfcp_fc_req_cache ; 
 scalar_t__ zfcp_fc_sg_setup_table (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct zfcp_fc_req *zfcp_fc_alloc_sg_env(int buf_num)
{
	struct zfcp_fc_req *fc_req;

	fc_req = kmem_cache_zalloc(zfcp_fc_req_cache, GFP_KERNEL);
	if (!fc_req)
		return NULL;

	if (zfcp_fc_sg_setup_table(&fc_req->sg_rsp, buf_num)) {
		kmem_cache_free(zfcp_fc_req_cache, fc_req);
		return NULL;
	}

	sg_init_one(&fc_req->sg_req, &fc_req->u.gpn_ft.req,
		    sizeof(struct zfcp_fc_gpn_ft_req));

	return fc_req;
}