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
struct csio_lnode {int flags; } ;

/* Variables and functions */
 int CSIO_LNF_LINK_ENABLE ; 
 int csio_fcoe_enable_link (struct csio_lnode*,int) ; 
 scalar_t__ csio_is_phys_ln (struct csio_lnode*) ; 

int
csio_lnode_start(struct csio_lnode *ln)
{
	int rv = 0;
	if (csio_is_phys_ln(ln) && !(ln->flags & CSIO_LNF_LINK_ENABLE)) {
		rv = csio_fcoe_enable_link(ln, 1);
		ln->flags |= CSIO_LNF_LINK_ENABLE;
	}

	return rv;
}