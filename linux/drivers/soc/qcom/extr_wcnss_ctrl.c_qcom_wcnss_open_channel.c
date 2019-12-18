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
struct wcnss_ctrl {TYPE_1__* channel; } ;
struct rpmsg_endpoint {int dummy; } ;
struct rpmsg_channel_info {void* dst; void* src; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rpmsg_rx_cb_t ;
struct TYPE_2__ {int /*<<< orphan*/  rpdev; } ;

/* Variables and functions */
 void* RPMSG_ADDR_ANY ; 
 struct rpmsg_endpoint* rpmsg_create_ept (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct rpmsg_channel_info) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int) ; 

struct rpmsg_endpoint *qcom_wcnss_open_channel(void *wcnss, const char *name, rpmsg_rx_cb_t cb, void *priv)
{
	struct rpmsg_channel_info chinfo;
	struct wcnss_ctrl *_wcnss = wcnss;

	strscpy(chinfo.name, name, sizeof(chinfo.name));
	chinfo.src = RPMSG_ADDR_ANY;
	chinfo.dst = RPMSG_ADDR_ANY;

	return rpmsg_create_ept(_wcnss->channel->rpdev, cb, priv, chinfo);
}