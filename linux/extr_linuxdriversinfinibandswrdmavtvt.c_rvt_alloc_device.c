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
struct rvt_ibport {int dummy; } ;
struct rvt_dev_info {int /*<<< orphan*/  ibdev; int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ib_alloc_device (size_t) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 

struct rvt_dev_info *rvt_alloc_device(size_t size, int nports)
{
	struct rvt_dev_info *rdi;

	rdi = (struct rvt_dev_info *)ib_alloc_device(size);
	if (!rdi)
		return rdi;

	rdi->ports = kcalloc(nports,
			     sizeof(struct rvt_ibport **),
			     GFP_KERNEL);
	if (!rdi->ports)
		ib_dealloc_device(&rdi->ibdev);

	return rdi;
}