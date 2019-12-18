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
struct dasd_oos_message {int code; } ;
struct dasd_device {TYPE_1__* discipline; TYPE_2__* cdev; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* check_attention ) (struct dasd_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  POOL_EXHAUST 133 
#define  POOL_RELIEVE 132 
#define  POOL_WARN 131 
#define  REPO_EXHAUST 130 
#define  REPO_RELIEVE 129 
#define  REPO_WARN 128 
 int /*<<< orphan*/  dasd_eckd_oos_resume (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_eckd_read_ext_pool_info (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dasd_eckd_handle_oos(struct dasd_device *device, void *messages,
				 __u8 lpum)
{
	struct dasd_oos_message *oos = messages;

	switch (oos->code) {
	case REPO_WARN:
	case POOL_WARN:
		dev_warn(&device->cdev->dev,
			 "Extent pool usage has reached a critical value\n");
		dasd_eckd_oos_resume(device);
		break;
	case REPO_EXHAUST:
	case POOL_EXHAUST:
		dev_warn(&device->cdev->dev,
			 "Extent pool is exhausted\n");
		break;
	case REPO_RELIEVE:
	case POOL_RELIEVE:
		dev_info(&device->cdev->dev,
			 "Extent pool physical space constraint has been relieved\n");
		break;
	}

	/* In any case, update related data */
	dasd_eckd_read_ext_pool_info(device);

	/* to make sure there is no attention left schedule work again */
	device->discipline->check_attention(device, lpum);
}