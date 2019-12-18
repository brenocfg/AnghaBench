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
struct ib_udata {int dummy; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct hns_roce_ucontext {int /*<<< orphan*/  uar; int /*<<< orphan*/  page_mutex; int /*<<< orphan*/  page_list; } ;
struct hns_roce_ib_alloc_ucontext_resp {int /*<<< orphan*/  qp_tab_size; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  num_qps; } ;
struct hns_roce_dev {TYPE_1__ caps; int /*<<< orphan*/  active; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int EAGAIN ; 
 int HNS_ROCE_CAP_FLAG_RECORD_DB ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int hns_roce_uar_alloc (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_uar_free (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int ib_copy_to_udata (struct ib_udata*,struct hns_roce_ib_alloc_ucontext_resp*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_ucontext* to_hr_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int hns_roce_alloc_ucontext(struct ib_ucontext *uctx,
				   struct ib_udata *udata)
{
	int ret;
	struct hns_roce_ucontext *context = to_hr_ucontext(uctx);
	struct hns_roce_ib_alloc_ucontext_resp resp = {};
	struct hns_roce_dev *hr_dev = to_hr_dev(uctx->device);

	if (!hr_dev->active)
		return -EAGAIN;

	resp.qp_tab_size = hr_dev->caps.num_qps;

	ret = hns_roce_uar_alloc(hr_dev, &context->uar);
	if (ret)
		goto error_fail_uar_alloc;

	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) {
		INIT_LIST_HEAD(&context->page_list);
		mutex_init(&context->page_mutex);
	}

	ret = ib_copy_to_udata(udata, &resp, sizeof(resp));
	if (ret)
		goto error_fail_copy_to_udata;

	return 0;

error_fail_copy_to_udata:
	hns_roce_uar_free(hr_dev, &context->uar);

error_fail_uar_alloc:
	return ret;
}