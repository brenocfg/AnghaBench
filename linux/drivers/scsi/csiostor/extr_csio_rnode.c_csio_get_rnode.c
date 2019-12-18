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
typedef  int /*<<< orphan*/  uint32_t ;
struct csio_rnode {int /*<<< orphan*/  flowid; } ;
struct csio_lnode {int dummy; } ;

/* Variables and functions */
 struct csio_rnode* csio_alloc_rnode (struct csio_lnode*) ; 
 struct csio_rnode* csio_rn_lookup (struct csio_lnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct csio_rnode *
csio_get_rnode(struct csio_lnode *ln, uint32_t flowid)
{
	struct csio_rnode *rn;

	rn = csio_rn_lookup(ln, flowid);
	if (!rn) {
		rn = csio_alloc_rnode(ln);
		if (!rn)
			return NULL;

		rn->flowid = flowid;
	}

	return rn;
}