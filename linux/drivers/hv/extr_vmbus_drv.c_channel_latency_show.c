#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmbus_channel {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/ * monitor_pages; } ;

/* Variables and functions */
 int channel_latency (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__ vmbus_connection ; 

__attribute__((used)) static ssize_t channel_latency_show(struct vmbus_channel *channel,
				    char *buf)
{
	return sprintf(buf, "%d\n",
		       channel_latency(channel,
				       vmbus_connection.monitor_pages[1]));
}