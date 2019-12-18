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
struct rpmsg_endpoint {int dummy; } ;
struct glink_channel {int dummy; } ;

/* Variables and functions */
 int __qcom_glink_send (struct glink_channel*,void*,int,int) ; 
 struct glink_channel* to_glink_channel (struct rpmsg_endpoint*) ; 

__attribute__((used)) static int qcom_glink_trysend(struct rpmsg_endpoint *ept, void *data, int len)
{
	struct glink_channel *channel = to_glink_channel(ept);

	return __qcom_glink_send(channel, data, len, false);
}