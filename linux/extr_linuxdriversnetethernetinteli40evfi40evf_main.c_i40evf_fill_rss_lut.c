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
typedef  size_t u16 ;
struct i40evf_adapter {size_t rss_lut_size; size_t* rss_lut; size_t num_active_queues; } ;

/* Variables and functions */

__attribute__((used)) static void i40evf_fill_rss_lut(struct i40evf_adapter *adapter)
{
	u16 i;

	for (i = 0; i < adapter->rss_lut_size; i++)
		adapter->rss_lut[i] = i % adapter->num_active_queues;
}