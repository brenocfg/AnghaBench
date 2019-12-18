#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct atp {TYPE_1__* info; int /*<<< orphan*/  input; TYPE_2__* intf; scalar_t__* xy_cur; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int xsensors; int xsensors_17; int xfact; int /*<<< orphan*/  fuzz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int ATP_XSENSORS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_set_abs_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atp_detect_size(struct atp *dev)
{
	int i;

	/* 17" Powerbooks have extra X sensors */
	for (i = dev->info->xsensors; i < ATP_XSENSORS; i++) {
		if (dev->xy_cur[i]) {

			dev_info(&dev->intf->dev,
				"appletouch: 17\" model detected.\n");

			input_set_abs_params(dev->input, ABS_X, 0,
					     (dev->info->xsensors_17 - 1) *
							dev->info->xfact - 1,
					     dev->info->fuzz, 0);
			break;
		}
	}
}