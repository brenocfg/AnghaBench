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
typedef  size_t u8 ;
struct ibmvmc_buffer {scalar_t__ owner; scalar_t__ free; scalar_t__ valid; } ;
struct TYPE_4__ {struct ibmvmc_buffer* buffer; } ;
struct TYPE_3__ {size_t max_hmc_index; } ;

/* Variables and functions */
 scalar_t__ VMC_BUF_OWNER_ALPHA ; 
 TYPE_2__* hmcs ; 
 TYPE_1__ ibmvmc ; 
 unsigned long ibmvmc_max_buf_pool_size ; 

__attribute__((used)) static struct ibmvmc_buffer *ibmvmc_get_valid_hmc_buffer(u8 hmc_index)
{
	struct ibmvmc_buffer *buffer;
	struct ibmvmc_buffer *ret_buf = NULL;
	unsigned long i;

	if (hmc_index > ibmvmc.max_hmc_index)
		return NULL;

	buffer = hmcs[hmc_index].buffer;

	for (i = 0; i < ibmvmc_max_buf_pool_size; i++) {
		if (buffer[i].valid && buffer[i].free &&
		    buffer[i].owner == VMC_BUF_OWNER_ALPHA) {
			buffer[i].free = 0;
			ret_buf = &buffer[i];
			break;
		}
	}

	return ret_buf;
}