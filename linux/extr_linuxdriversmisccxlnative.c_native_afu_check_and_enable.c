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
struct cxl_afu {scalar_t__ enabled; int /*<<< orphan*/  adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_ok ) (int /*<<< orphan*/ ,struct cxl_afu*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int afu_enable (struct cxl_afu*) ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct cxl_afu*) ; 

__attribute__((used)) static int native_afu_check_and_enable(struct cxl_afu *afu)
{
	if (!cxl_ops->link_ok(afu->adapter, afu)) {
		WARN(1, "Refusing to enable afu while link down!\n");
		return -EIO;
	}
	if (afu->enabled)
		return 0;
	return afu_enable(afu);
}