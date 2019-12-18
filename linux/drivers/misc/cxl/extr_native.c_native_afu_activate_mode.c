#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cxl_afu {int modes_supported; TYPE_3__* adapter; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* link_ok ) (TYPE_3__*,struct cxl_afu*) ;} ;
struct TYPE_7__ {TYPE_2__* native; } ;
struct TYPE_6__ {TYPE_1__* sl_ops; } ;
struct TYPE_5__ {int (* activate_dedicated_process ) (struct cxl_afu*) ;} ;

/* Variables and functions */
 int CXL_MODE_DEDICATED ; 
 int CXL_MODE_DIRECTED ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int activate_afu_directed (struct cxl_afu*) ; 
 TYPE_4__* cxl_ops ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct cxl_afu*) ; 
 int stub2 (struct cxl_afu*) ; 

__attribute__((used)) static int native_afu_activate_mode(struct cxl_afu *afu, int mode)
{
	if (!mode)
		return 0;
	if (!(mode & afu->modes_supported))
		return -EINVAL;

	if (!cxl_ops->link_ok(afu->adapter, afu)) {
		WARN(1, "Device link is down, refusing to activate!\n");
		return -EIO;
	}

	if (mode == CXL_MODE_DIRECTED)
		return activate_afu_directed(afu);
	if ((mode == CXL_MODE_DEDICATED) &&
	    (afu->adapter->native->sl_ops->activate_dedicated_process))
		return afu->adapter->native->sl_ops->activate_dedicated_process(afu);

	return -EINVAL;
}