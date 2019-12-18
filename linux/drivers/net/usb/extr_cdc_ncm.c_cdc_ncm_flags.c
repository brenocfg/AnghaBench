#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {TYPE_1__* intf; scalar_t__* data; } ;
struct cdc_ncm_ctx {TYPE_3__* func_desc; TYPE_2__* mbim_desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  bmNetworkCapabilities; } ;
struct TYPE_5__ {int /*<<< orphan*/  bmNetworkCapabilities; } ;
struct TYPE_4__ {int /*<<< orphan*/  cur_altsetting; } ;

/* Variables and functions */
 scalar_t__ cdc_ncm_comm_intf_is_mbim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 cdc_ncm_flags(struct usbnet *dev)
{
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)dev->data[0];

	if (cdc_ncm_comm_intf_is_mbim(dev->intf->cur_altsetting) && ctx->mbim_desc)
		return ctx->mbim_desc->bmNetworkCapabilities;
	if (ctx->func_desc)
		return ctx->func_desc->bmNetworkCapabilities;
	return 0;
}