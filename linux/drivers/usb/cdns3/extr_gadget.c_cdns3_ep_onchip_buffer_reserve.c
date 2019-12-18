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
struct cdns3_device {int onchip_buffers; int onchip_used_size; int out_mem_is_allocated; } ;

/* Variables and functions */
 int EPERM ; 

__attribute__((used)) static int cdns3_ep_onchip_buffer_reserve(struct cdns3_device *priv_dev,
					  int size, int is_in)
{
	int remained;

	/* 2KB are reserved for EP0*/
	remained = priv_dev->onchip_buffers - priv_dev->onchip_used_size - 2;

	if (is_in) {
		if (remained < size)
			return -EPERM;

		priv_dev->onchip_used_size += size;
	} else {
		int required;

		/**
		 *  ALL OUT EPs are shared the same chunk onchip memory, so
		 * driver checks if it already has assigned enough buffers
		 */
		if (priv_dev->out_mem_is_allocated >= size)
			return 0;

		required = size - priv_dev->out_mem_is_allocated;

		if (required > remained)
			return -EPERM;

		priv_dev->out_mem_is_allocated += required;
		priv_dev->onchip_used_size += required;
	}

	return 0;
}