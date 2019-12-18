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
struct isp_bus_cfg {int dummy; } ;
struct isp_async_subdev {struct isp_bus_cfg bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct isp_async_subdev* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isp_alloc_isd(struct isp_async_subdev **isd,
			 struct isp_bus_cfg **buscfg)
{
	struct isp_async_subdev *__isd;

	__isd = kzalloc(sizeof(*__isd), GFP_KERNEL);
	if (!__isd)
		return -ENOMEM;

	*isd = __isd;
	*buscfg = &__isd->bus;

	return 0;
}