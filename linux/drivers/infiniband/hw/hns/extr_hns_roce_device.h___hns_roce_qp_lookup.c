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
typedef  int u32 ;
struct hns_roce_qp {int dummy; } ;
struct TYPE_2__ {int num_qps; } ;
struct hns_roce_dev {TYPE_1__ caps; int /*<<< orphan*/  qp_table_xa; } ;

/* Variables and functions */
 struct hns_roce_qp* xa_load (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct hns_roce_qp
	*__hns_roce_qp_lookup(struct hns_roce_dev *hr_dev, u32 qpn)
{
	return xa_load(&hr_dev->qp_table_xa, qpn & (hr_dev->caps.num_qps - 1));
}