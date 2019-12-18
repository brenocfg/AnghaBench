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
struct se_session {int /*<<< orphan*/ * sess_cmd_map; int /*<<< orphan*/  sess_tag_pool; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int __GFP_RETRY_MAYFAIL ; 
 int /*<<< orphan*/ * kvcalloc (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int sbitmap_queue_init_node (int /*<<< orphan*/ *,unsigned int,int,int,int,int /*<<< orphan*/ ) ; 

int transport_alloc_session_tags(struct se_session *se_sess,
			         unsigned int tag_num, unsigned int tag_size)
{
	int rc;

	se_sess->sess_cmd_map = kvcalloc(tag_size, tag_num,
					 GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	if (!se_sess->sess_cmd_map) {
		pr_err("Unable to allocate se_sess->sess_cmd_map\n");
		return -ENOMEM;
	}

	rc = sbitmap_queue_init_node(&se_sess->sess_tag_pool, tag_num, -1,
			false, GFP_KERNEL, NUMA_NO_NODE);
	if (rc < 0) {
		pr_err("Unable to init se_sess->sess_tag_pool,"
			" tag_num: %u\n", tag_num);
		kvfree(se_sess->sess_cmd_map);
		se_sess->sess_cmd_map = NULL;
		return -ENOMEM;
	}

	return 0;
}