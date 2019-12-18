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
struct cxgbi_hba {TYPE_2__* ndev; int /*<<< orphan*/  ipv4addr; TYPE_1__* cdev; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int CXGBI_FLAG_IPV4_SET ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cxgbi_set_iscsi_ipv4(struct cxgbi_hba *chba, __be32 ipaddr)
{
	if (chba->cdev->flags & CXGBI_FLAG_IPV4_SET)
		chba->ipv4addr = ipaddr;
	else
		pr_info("set iscsi ipv4 NOT supported, using %s ipv4.\n",
			chba->ndev->name);
}