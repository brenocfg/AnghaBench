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
struct host1x_channel {int dummy; } ;
struct host1x {TYPE_1__* channel_op; } ;
struct TYPE_2__ {int (* init ) (struct host1x_channel*,struct host1x*,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (struct host1x_channel*,struct host1x*,unsigned int) ; 

__attribute__((used)) static inline int host1x_hw_channel_init(struct host1x *host,
					 struct host1x_channel *channel,
					 unsigned int id)
{
	return host->channel_op->init(channel, host, id);
}