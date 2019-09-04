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
typedef  int /*<<< orphan*/  u32 ;
struct __vxge_hw_fifo {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  vxge_hw_channel_dtr_count (int /*<<< orphan*/ *) ; 

u32 vxge_hw_fifo_free_txdl_count_get(struct __vxge_hw_fifo *fifoh)
{
	return vxge_hw_channel_dtr_count(&fifoh->channel);
}