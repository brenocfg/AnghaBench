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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ next_to_use; } ;
struct TYPE_4__ {TYPE_1__ csq; } ;
struct hns_roce_v2_priv {TYPE_2__ cmq; } ;
struct hns_roce_dev {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCEE_TX_CMQ_HEAD_REG ; 
 scalar_t__ roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_cmq_csq_done(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	u32 head = roce_read(hr_dev, ROCEE_TX_CMQ_HEAD_REG);

	return head == priv->cmq.csq.next_to_use;
}