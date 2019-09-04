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
struct hv_ring_buffer_info {int dummy; } ;
struct vmbus_channel {struct hv_ring_buffer_info outbound; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int hv_get_bytes_to_write (struct hv_ring_buffer_info const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t write_avail_show(const struct vmbus_channel *channel, char *buf)
{
	const struct hv_ring_buffer_info *rbi = &channel->outbound;

	return sprintf(buf, "%u\n", hv_get_bytes_to_write(rbi));
}