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
struct hv_ring_buffer_info {int /*<<< orphan*/  ring_buffer_mutex; int /*<<< orphan*/  ring_buffer; } ;
struct vmbus_channel {struct hv_ring_buffer_info inbound; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int hv_get_bytes_to_read (struct hv_ring_buffer_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t read_avail_show(struct vmbus_channel *channel, char *buf)
{
	struct hv_ring_buffer_info *rbi = &channel->inbound;
	ssize_t ret;

	mutex_lock(&rbi->ring_buffer_mutex);
	if (!rbi->ring_buffer) {
		mutex_unlock(&rbi->ring_buffer_mutex);
		return -EINVAL;
	}

	ret = sprintf(buf, "%u\n", hv_get_bytes_to_read(rbi));
	mutex_unlock(&rbi->ring_buffer_mutex);
	return ret;
}