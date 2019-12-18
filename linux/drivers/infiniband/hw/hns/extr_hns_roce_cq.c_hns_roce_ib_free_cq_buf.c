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
struct TYPE_2__ {int cq_entry_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;
struct hns_roce_cq_buf {int /*<<< orphan*/  hr_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_ib_free_cq_buf(struct hns_roce_dev *hr_dev,
				    struct hns_roce_cq_buf *buf, int cqe)
{
	hns_roce_buf_free(hr_dev, (cqe + 1) * hr_dev->caps.cq_entry_sz,
			  &buf->hr_buf);
}