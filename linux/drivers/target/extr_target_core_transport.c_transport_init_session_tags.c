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
struct se_session {int dummy; } ;
typedef  enum target_prot_op { ____Placeholder_target_prot_op } target_prot_op ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct se_session* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct se_session*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 struct se_session* transport_alloc_session (int) ; 
 int transport_alloc_session_tags (struct se_session*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  transport_free_session (struct se_session*) ; 

__attribute__((used)) static struct se_session *
transport_init_session_tags(unsigned int tag_num, unsigned int tag_size,
			    enum target_prot_op sup_prot_ops)
{
	struct se_session *se_sess;
	int rc;

	if (tag_num != 0 && !tag_size) {
		pr_err("init_session_tags called with percpu-ida tag_num:"
		       " %u, but zero tag_size\n", tag_num);
		return ERR_PTR(-EINVAL);
	}
	if (!tag_num && tag_size) {
		pr_err("init_session_tags called with percpu-ida tag_size:"
		       " %u, but zero tag_num\n", tag_size);
		return ERR_PTR(-EINVAL);
	}

	se_sess = transport_alloc_session(sup_prot_ops);
	if (IS_ERR(se_sess))
		return se_sess;

	rc = transport_alloc_session_tags(se_sess, tag_num, tag_size);
	if (rc < 0) {
		transport_free_session(se_sess);
		return ERR_PTR(-ENOMEM);
	}

	return se_sess;
}