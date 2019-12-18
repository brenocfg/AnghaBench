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
struct se_session {int sup_prot_ops; } ;
typedef  enum target_prot_op { ____Placeholder_target_prot_op } target_prot_op ;

/* Variables and functions */
 int ENOMEM ; 
 struct se_session* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct se_session*) ; 
 struct se_session* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  se_sess_cache ; 
 int transport_init_session (struct se_session*) ; 

struct se_session *transport_alloc_session(enum target_prot_op sup_prot_ops)
{
	struct se_session *se_sess;
	int ret;

	se_sess = kmem_cache_zalloc(se_sess_cache, GFP_KERNEL);
	if (!se_sess) {
		pr_err("Unable to allocate struct se_session from"
				" se_sess_cache\n");
		return ERR_PTR(-ENOMEM);
	}
	ret = transport_init_session(se_sess);
	if (ret < 0) {
		kmem_cache_free(se_sess_cache, se_sess);
		return ERR_PTR(ret);
	}
	se_sess->sup_prot_ops = sup_prot_ops;

	return se_sess;
}