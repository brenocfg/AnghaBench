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
struct rdma_ah_attr {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 

struct ib_ah *usnic_ib_create_ah(struct ib_pd *pd,
				 struct rdma_ah_attr *ah_attr,
				 struct ib_udata *udata)

{
	usnic_dbg("\n");
	return ERR_PTR(-EPERM);
}