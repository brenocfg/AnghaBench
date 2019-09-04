#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_dcb {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* query_cee_param ) (struct qlcnic_dcb*,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct qlcnic_dcb*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
qlcnic_dcb_query_cee_param(struct qlcnic_dcb *dcb, char *buf, u8 type)
{
	if (dcb && dcb->ops->query_cee_param)
		return dcb->ops->query_cee_param(dcb, buf, type);

	return 0;
}