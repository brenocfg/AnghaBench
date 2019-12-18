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
struct parisc_device {int /*<<< orphan*/  dev; } ;
struct ioc {int dummy; } ;
struct ibase_data_struct {int ioc_num; struct ioc* ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct ibase_data_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_ibase_imask_callback ; 

__attribute__((used)) static void 
setup_ibase_imask(struct parisc_device *sba, struct ioc *ioc, int ioc_num)
{
	struct ibase_data_struct ibase_data = {
		.ioc		= ioc,
		.ioc_num	= ioc_num,
	};

	device_for_each_child(&sba->dev, &ibase_data,
			      setup_ibase_imask_callback);
}