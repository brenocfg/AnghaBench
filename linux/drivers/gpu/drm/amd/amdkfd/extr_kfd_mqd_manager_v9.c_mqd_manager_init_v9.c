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
struct v9_sdma_mqd {int dummy; } ;
struct v9_mqd {int dummy; } ;
struct mqd_manager {int mqd_size; void* debugfs_show_mqd; void* is_occupied; void* destroy_mqd; void* update_mqd; void* load_mqd; void* free_mqd; void* init_mqd; void* allocate_mqd; int /*<<< orphan*/  get_wave_state; struct kfd_dev* dev; } ;
struct kfd_dev {int dummy; } ;
typedef  enum KFD_MQD_TYPE { ____Placeholder_KFD_MQD_TYPE } KFD_MQD_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  KFD_MQD_TYPE_COMPUTE 132 
#define  KFD_MQD_TYPE_CP 131 
#define  KFD_MQD_TYPE_DIQ 130 
#define  KFD_MQD_TYPE_HIQ 129 
 int KFD_MQD_TYPE_MAX ; 
#define  KFD_MQD_TYPE_SDMA 128 
 scalar_t__ WARN_ON (int) ; 
 void* allocate_hiq_mqd ; 
 void* allocate_mqd ; 
 void* allocate_sdma_mqd ; 
 void* debugfs_show_mqd ; 
 void* debugfs_show_mqd_sdma ; 
 void* destroy_mqd ; 
 void* destroy_mqd_sdma ; 
 void* free_mqd ; 
 void* free_mqd_hiq_sdma ; 
 int /*<<< orphan*/  get_wave_state ; 
 void* init_mqd ; 
 void* init_mqd_hiq ; 
 void* init_mqd_sdma ; 
 void* is_occupied ; 
 void* is_occupied_sdma ; 
 int /*<<< orphan*/  kfree (struct mqd_manager*) ; 
 struct mqd_manager* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* load_mqd ; 
 void* load_mqd_sdma ; 
 void* update_mqd ; 
 void* update_mqd_hiq ; 
 void* update_mqd_sdma ; 

struct mqd_manager *mqd_manager_init_v9(enum KFD_MQD_TYPE type,
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
		mqd->allocate_mqd = allocate_mqd;
		mqd->init_mqd = init_mqd;
		mqd->free_mqd = free_mqd;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->get_wave_state = get_wave_state;
		mqd->mqd_size = sizeof(struct v9_mqd);
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		break;
	case KFD_MQD_TYPE_HIQ:
		mqd->allocate_mqd = allocate_hiq_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->free_mqd = free_mqd_hiq_sdma;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd_hiq;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->mqd_size = sizeof(struct v9_mqd);
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		break;
	case KFD_MQD_TYPE_DIQ:
		mqd->allocate_mqd = allocate_hiq_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->free_mqd = free_mqd;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd_hiq;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->mqd_size = sizeof(struct v9_mqd);
#if defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#endif
		break;
	case KFD_MQD_TYPE_SDMA:
		mqd->allocate_mqd = allocate_sdma_mqd;
		mqd->init_mqd = init_mqd_sdma;
		mqd->free_mqd = free_mqd_hiq_sdma;
		mqd->load_mqd = load_mqd_sdma;
		mqd->update_mqd = update_mqd_sdma;
		mqd->destroy_mqd = destroy_mqd_sdma;
		mqd->is_occupied = is_occupied_sdma;
		mqd->mqd_size = sizeof(struct v9_sdma_mqd);
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