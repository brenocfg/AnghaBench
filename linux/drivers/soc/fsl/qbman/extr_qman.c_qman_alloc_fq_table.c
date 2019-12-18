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
typedef  int u32 ;
struct qman_fq {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 int /*<<< orphan*/  fq_table ; 
 int num_fqids ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 

int qman_alloc_fq_table(u32 _num_fqids)
{
	num_fqids = _num_fqids;

	fq_table = vzalloc(array3_size(sizeof(struct qman_fq *),
				       num_fqids, 2));
	if (!fq_table)
		return -ENOMEM;

	pr_debug("Allocated fq lookup table at %p, entry count %u\n",
		 fq_table, num_fqids * 2);
	return 0;
}