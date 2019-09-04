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
struct mqd_manager {void* is_occupied; void* destroy_mqd; int /*<<< orphan*/  update_mqd; void* load_mqd; void* uninit_mqd; int /*<<< orphan*/  init_mqd; struct kfd_dev* dev; } ;
struct kfd_dev {int dummy; } ;
typedef  enum KFD_MQD_TYPE { ____Placeholder_KFD_MQD_TYPE } KFD_MQD_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  KFD_MQD_TYPE_COMPUTE 131 
#define  KFD_MQD_TYPE_CP 130 
#define  KFD_MQD_TYPE_HIQ 129 
 int KFD_MQD_TYPE_MAX ; 
#define  KFD_MQD_TYPE_SDMA 128 
 scalar_t__ WARN_ON (int) ; 
 void* destroy_mqd ; 
 void* destroy_mqd_sdma ; 
 int /*<<< orphan*/  init_mqd ; 
 int /*<<< orphan*/  init_mqd_hiq ; 
 int /*<<< orphan*/  init_mqd_sdma ; 
 void* is_occupied ; 
 void* is_occupied_sdma ; 
 int /*<<< orphan*/  kfree (struct mqd_manager*) ; 
 struct mqd_manager* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* load_mqd ; 
 void* load_mqd_sdma ; 
 void* uninit_mqd ; 
 void* uninit_mqd_sdma ; 
 int /*<<< orphan*/  update_mqd ; 
 int /*<<< orphan*/  update_mqd_hiq ; 
 int /*<<< orphan*/  update_mqd_sdma ; 

struct mqd_manager *mqd_manager_init_vi(enum KFD_MQD_TYPE type,
		struct kfd_dev *dev)
{
	struct mqd_manager *mqd;

	if (WARN_ON(type >= KFD_MQD_TYPE_MAX))
		return NULL;

	mqd = kzalloc(sizeof(*mqd), GFP_KERNEL);
	if (!mqd)
		return NULL;

	mqd->dev = dev;

	switch (type) {
	case KFD_MQD_TYPE_CP:
	case KFD_MQD_TYPE_COMPUTE:
		mqd->init_mqd = init_mqd;
		mqd->uninit_mqd = uninit_mqd;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		break;
	case KFD_MQD_TYPE_HIQ:
		mqd->init_mqd = init_mqd_hiq;
		mqd->uninit_mqd = uninit_mqd;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd_hiq;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		break;
	case KFD_MQD_TYPE_SDMA:
		mqd->init_mqd = init_mqd_sdma;
		mqd->uninit_mqd = uninit_mqd_sdma;
		mqd->load_mqd = load_mqd_sdma;
		mqd->update_mqd = update_mqd_sdma;
		mqd->destroy_mqd = destroy_mqd_sdma;
		mqd->is_occupied = is_occupied_sdma;
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd_sdma;
#endif
		break;
	default:
		kfree(mqd);
		return NULL;
	}

	return mqd;
}