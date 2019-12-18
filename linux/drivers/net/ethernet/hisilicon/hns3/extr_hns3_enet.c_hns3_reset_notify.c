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
struct hnae3_handle {int dummy; } ;
typedef  enum hnae3_reset_notify_type { ____Placeholder_hnae3_reset_notify_type } hnae3_reset_notify_type ;

/* Variables and functions */
#define  HNAE3_DOWN_CLIENT 132 
#define  HNAE3_INIT_CLIENT 131 
#define  HNAE3_RESTORE_CLIENT 130 
#define  HNAE3_UNINIT_CLIENT 129 
#define  HNAE3_UP_CLIENT 128 
 int hns3_reset_notify_down_enet (struct hnae3_handle*) ; 
 int hns3_reset_notify_init_enet (struct hnae3_handle*) ; 
 int hns3_reset_notify_restore_enet (struct hnae3_handle*) ; 
 int hns3_reset_notify_uninit_enet (struct hnae3_handle*) ; 
 int hns3_reset_notify_up_enet (struct hnae3_handle*) ; 

__attribute__((used)) static int hns3_reset_notify(struct hnae3_handle *handle,
			     enum hnae3_reset_notify_type type)
{
	int ret = 0;

	switch (type) {
	case HNAE3_UP_CLIENT:
		ret = hns3_reset_notify_up_enet(handle);
		break;
	case HNAE3_DOWN_CLIENT:
		ret = hns3_reset_notify_down_enet(handle);
		break;
	case HNAE3_INIT_CLIENT:
		ret = hns3_reset_notify_init_enet(handle);
		break;
	case HNAE3_UNINIT_CLIENT:
		ret = hns3_reset_notify_uninit_enet(handle);
		break;
	case HNAE3_RESTORE_CLIENT:
		ret = hns3_reset_notify_restore_enet(handle);
		break;
	default:
		break;
	}

	return ret;
}