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
 int RX_QUEUE_ENTRIES ; 

__attribute__((used)) static int ftmac100_next_rx_pointer(int pointer)
{
	return (pointer + 1) & (RX_QUEUE_ENTRIES - 1);
}