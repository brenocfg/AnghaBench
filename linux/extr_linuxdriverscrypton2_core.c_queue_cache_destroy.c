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
 int HV_NCS_QTYPE_CWQ ; 
 int HV_NCS_QTYPE_MAU ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** queue_cache ; 

__attribute__((used)) static void queue_cache_destroy(void)
{
	kmem_cache_destroy(queue_cache[HV_NCS_QTYPE_MAU - 1]);
	kmem_cache_destroy(queue_cache[HV_NCS_QTYPE_CWQ - 1]);
	queue_cache[HV_NCS_QTYPE_MAU - 1] = NULL;
	queue_cache[HV_NCS_QTYPE_CWQ - 1] = NULL;
}