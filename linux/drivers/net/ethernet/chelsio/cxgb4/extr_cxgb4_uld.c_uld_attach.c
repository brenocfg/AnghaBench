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
struct cxgb4_lld_info {int dummy; } ;
struct adapter {int flags; TYPE_1__* uld; int /*<<< orphan*/  pdev_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* state_change ) (void*,int /*<<< orphan*/ ) ;void* handle; int /*<<< orphan*/  name; void* (* add ) (struct cxgb4_lld_info*) ;} ;

/* Variables and functions */
 int CXGB4_FULL_INIT_DONE ; 
 int /*<<< orphan*/  CXGB4_STATE_UP ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 void* stub1 (struct cxgb4_lld_info*) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_register_netevent_notifier () ; 
 int /*<<< orphan*/  uld_init (struct adapter*,struct cxgb4_lld_info*) ; 
 int /*<<< orphan*/  uld_queue_init (struct adapter*,unsigned int,struct cxgb4_lld_info*) ; 

__attribute__((used)) static int uld_attach(struct adapter *adap, unsigned int uld)
{
	struct cxgb4_lld_info lli;
	void *handle;

	uld_init(adap, &lli);
	uld_queue_init(adap, uld, &lli);

	handle = adap->uld[uld].add(&lli);
	if (IS_ERR(handle)) {
		dev_warn(adap->pdev_dev,
			 "could not attach to the %s driver, error %ld\n",
			 adap->uld[uld].name, PTR_ERR(handle));
		return PTR_ERR(handle);
	}

	adap->uld[uld].handle = handle;
	t4_register_netevent_notifier();

	if (adap->flags & CXGB4_FULL_INIT_DONE)
		adap->uld[uld].state_change(handle, CXGB4_STATE_UP);

	return 0;
}