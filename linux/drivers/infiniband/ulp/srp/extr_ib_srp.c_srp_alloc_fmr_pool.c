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
struct srp_target_port {int mr_pool_size; TYPE_1__* srp_host; } ;
struct srp_device {int /*<<< orphan*/  pd; int /*<<< orphan*/  mr_page_size; int /*<<< orphan*/  max_pages_per_mr; } ;
struct ib_fmr_pool_param {int pool_size; int dirty_watermark; int cache; int access; int /*<<< orphan*/  page_shift; int /*<<< orphan*/  max_pages_per_fmr; } ;
struct ib_fmr_pool {int dummy; } ;
typedef  int /*<<< orphan*/  fmr_param ;
struct TYPE_2__ {struct srp_device* srp_dev; } ;

/* Variables and functions */
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 struct ib_fmr_pool* ib_create_fmr_pool (int /*<<< orphan*/ ,struct ib_fmr_pool_param*) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_fmr_pool_param*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ib_fmr_pool *srp_alloc_fmr_pool(struct srp_target_port *target)
{
	struct srp_device *dev = target->srp_host->srp_dev;
	struct ib_fmr_pool_param fmr_param;

	memset(&fmr_param, 0, sizeof(fmr_param));
	fmr_param.pool_size	    = target->mr_pool_size;
	fmr_param.dirty_watermark   = fmr_param.pool_size / 4;
	fmr_param.cache		    = 1;
	fmr_param.max_pages_per_fmr = dev->max_pages_per_mr;
	fmr_param.page_shift	    = ilog2(dev->mr_page_size);
	fmr_param.access	    = (IB_ACCESS_LOCAL_WRITE |
				       IB_ACCESS_REMOTE_WRITE |
				       IB_ACCESS_REMOTE_READ);

	return ib_create_fmr_pool(dev->pd, &fmr_param);
}