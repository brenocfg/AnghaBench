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
typedef  enum kfd_queue_type { ____Placeholder_kfd_queue_type } kfd_queue_type ;
typedef  enum KFD_MQD_TYPE { ____Placeholder_KFD_MQD_TYPE } KFD_MQD_TYPE ;

/* Variables and functions */
 int KFD_MQD_TYPE_CP ; 
 int KFD_MQD_TYPE_SDMA ; 
 int KFD_QUEUE_TYPE_SDMA ; 

__attribute__((used)) static inline
enum KFD_MQD_TYPE get_mqd_type_from_queue_type(enum kfd_queue_type type)
{
	if (type == KFD_QUEUE_TYPE_SDMA)
		return KFD_MQD_TYPE_SDMA;
	return KFD_MQD_TYPE_CP;
}