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
typedef  int uint32_t ;
struct vi_sdma_mqd {int sdma_engine_id; int sdma_queue_id; } ;

/* Variables and functions */
 int KFD_VI_SDMA_QUEUE_OFFSET ; 
 int SDMA1_REGISTER_OFFSET ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static inline uint32_t get_sdma_base_addr(struct vi_sdma_mqd *m)
{
	uint32_t retval;

	retval = m->sdma_engine_id * SDMA1_REGISTER_OFFSET +
		m->sdma_queue_id * KFD_VI_SDMA_QUEUE_OFFSET;
	pr_debug("sdma base address: 0x%x\n", retval);

	return retval;
}