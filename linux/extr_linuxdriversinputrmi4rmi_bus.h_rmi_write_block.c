#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct rmi_device {TYPE_2__* xport; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* write_block ) (TYPE_2__*,int /*<<< orphan*/ ,void const*,size_t) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static inline int rmi_write_block(struct rmi_device *d, u16 addr,
				  const void *buf, size_t len)
{
	return d->xport->ops->write_block(d->xport, addr, buf, len);
}