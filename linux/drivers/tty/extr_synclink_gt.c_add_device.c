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
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct slgt_info {size_t line; int max_frame_size; int /*<<< orphan*/  irq_level; int /*<<< orphan*/  phys_reg_addr; int /*<<< orphan*/  device_name; TYPE_2__ params; TYPE_1__* pdev; struct slgt_info* next_device; } ;
struct TYPE_3__ {int device; } ;

/* Variables and functions */
 size_t MAX_DEVICES ; 
 int /*<<< orphan*/  MGSL_MODE_ASYNC ; 
#define  SYNCLINK_AC_DEVICE_ID 131 
#define  SYNCLINK_GT2_DEVICE_ID 130 
#define  SYNCLINK_GT4_DEVICE_ID 129 
#define  SYNCLINK_GT_DEVICE_ID 128 
 int /*<<< orphan*/  hdlcdev_init (struct slgt_info*) ; 
 int* maxframe ; 
 int /*<<< orphan*/  printk (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t slgt_device_count ; 
 struct slgt_info* slgt_device_list ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,size_t) ; 
 char* tty_dev_prefix ; 

__attribute__((used)) static void add_device(struct slgt_info *info)
{
	char *devstr;

	info->next_device = NULL;
	info->line = slgt_device_count;
	sprintf(info->device_name, "%s%d", tty_dev_prefix, info->line);

	if (info->line < MAX_DEVICES) {
		if (maxframe[info->line])
			info->max_frame_size = maxframe[info->line];
	}

	slgt_device_count++;

	if (!slgt_device_list)
		slgt_device_list = info;
	else {
		struct slgt_info *current_dev = slgt_device_list;
		while(current_dev->next_device)
			current_dev = current_dev->next_device;
		current_dev->next_device = info;
	}

	if (info->max_frame_size < 4096)
		info->max_frame_size = 4096;
	else if (info->max_frame_size > 65535)
		info->max_frame_size = 65535;

	switch(info->pdev->device) {
	case SYNCLINK_GT_DEVICE_ID:
		devstr = "GT";
		break;
	case SYNCLINK_GT2_DEVICE_ID:
		devstr = "GT2";
		break;
	case SYNCLINK_GT4_DEVICE_ID:
		devstr = "GT4";
		break;
	case SYNCLINK_AC_DEVICE_ID:
		devstr = "AC";
		info->params.mode = MGSL_MODE_ASYNC;
		break;
	default:
		devstr = "(unknown model)";
	}
	printk("SyncLink %s %s IO=%08x IRQ=%d MaxFrameSize=%u\n",
		devstr, info->device_name, info->phys_reg_addr,
		info->irq_level, info->max_frame_size);

#if SYNCLINK_GENERIC_HDLC
	hdlcdev_init(info);
#endif
}