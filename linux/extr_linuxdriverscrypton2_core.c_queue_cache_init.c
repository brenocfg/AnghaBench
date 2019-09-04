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

/* Variables and functions */
 int CWQ_ENTRY_SIZE ; 
 int CWQ_NUM_ENTRIES ; 
 int ENOMEM ; 
 int HV_NCS_QTYPE_CWQ ; 
 int HV_NCS_QTYPE_MAU ; 
 int MAU_ENTRY_SIZE ; 
 int MAU_NUM_ENTRIES ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** queue_cache ; 

__attribute__((used)) static int queue_cache_init(void)
{
	if (!queue_cache[HV_NCS_QTYPE_MAU - 1])
		queue_cache[HV_NCS_QTYPE_MAU - 1] =
			kmem_cache_create("mau_queue",
					  (MAU_NUM_ENTRIES *
					   MAU_ENTRY_SIZE),
					  MAU_ENTRY_SIZE, 0, NULL);
	if (!queue_cache[HV_NCS_QTYPE_MAU - 1])
		return -ENOMEM;

	if (!queue_cache[HV_NCS_QTYPE_CWQ - 1])
		queue_cache[HV_NCS_QTYPE_CWQ - 1] =
			kmem_cache_create("cwq_queue",
					  (CWQ_NUM_ENTRIES *
					   CWQ_ENTRY_SIZE),
					  CWQ_ENTRY_SIZE, 0, NULL);
	if (!queue_cache[HV_NCS_QTYPE_CWQ - 1]) {
		kmem_cache_destroy(queue_cache[HV_NCS_QTYPE_MAU - 1]);
		queue_cache[HV_NCS_QTYPE_MAU - 1] = NULL;
		return -ENOMEM;
	}
	return 0;
}