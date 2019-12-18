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
typedef  size_t u8 ;
struct qed_ll2_info {size_t my_id; } ;
struct qed_hwfn {struct qed_ll2_info* p_ll2_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t QED_MAX_NUM_OF_LL2_CONNECTIONS ; 
 struct qed_ll2_info* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 

int qed_ll2_alloc(struct qed_hwfn *p_hwfn)
{
	struct qed_ll2_info *p_ll2_connections;
	u8 i;

	/* Allocate LL2's set struct */
	p_ll2_connections = kcalloc(QED_MAX_NUM_OF_LL2_CONNECTIONS,
				    sizeof(struct qed_ll2_info), GFP_KERNEL);
	if (!p_ll2_connections) {
		DP_NOTICE(p_hwfn, "Failed to allocate `struct qed_ll2'\n");
		return -ENOMEM;
	}

	for (i = 0; i < QED_MAX_NUM_OF_LL2_CONNECTIONS; i++)
		p_ll2_connections[i].my_id = i;

	p_hwfn->p_ll2_info = p_ll2_connections;
	return 0;
}