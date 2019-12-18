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
struct uss720_async_request {int /*<<< orphan*/  ref_count; } ;
struct parport_uss720_private {TYPE_1__* usbdev; } ;
struct parport {struct parport_uss720_private* private_data; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  destroy_async ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct uss720_async_request* submit_async_request (struct parport_uss720_private*,int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_1284_register(struct parport *pp, unsigned char reg, unsigned char val, gfp_t mem_flags)
{
	struct parport_uss720_private *priv;
	struct uss720_async_request *rq;

	if (!pp)
		return -EIO;
	priv = pp->private_data;
	rq = submit_async_request(priv, 4, 0x40, (((unsigned int)reg) << 8) | val, 0, mem_flags);
	if (!rq) {
		dev_err(&priv->usbdev->dev, "set_1284_register(%u,%u) failed",
			(unsigned int)reg, (unsigned int)val);
		return -EIO;
	}
	kref_put(&rq->ref_count, destroy_async);
	return 0;
}