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
struct format_check_t {int dummy; } ;
struct dasd_device {TYPE_1__* discipline; } ;
struct dasd_block {struct dasd_device* base; } ;
struct TYPE_2__ {int (* check_device_format ) (struct dasd_device*,struct format_check_t*,int) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTTY ; 
 int stub1 (struct dasd_device*,struct format_check_t*,int) ; 
 int stub2 (struct dasd_device*,struct format_check_t*,int) ; 

__attribute__((used)) static int dasd_check_format(struct dasd_block *block,
			     struct format_check_t *cdata)
{
	struct dasd_device *base;
	int rc;

	base = block->base;
	if (!base->discipline->check_device_format)
		return -ENOTTY;

	rc = base->discipline->check_device_format(base, cdata, 1);
	if (rc == -EAGAIN)
		rc = base->discipline->check_device_format(base, cdata, 0);

	return rc;
}