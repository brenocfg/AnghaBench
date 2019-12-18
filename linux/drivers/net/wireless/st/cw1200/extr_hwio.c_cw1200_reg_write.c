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
typedef  int /*<<< orphan*/  u16 ;
struct cw1200_common {int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int __cw1200_reg_write (struct cw1200_common*,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int cw1200_reg_write(struct cw1200_common *priv, u16 addr, const void *buf,
			size_t buf_len)
{
	int ret;
	priv->hwbus_ops->lock(priv->hwbus_priv);
	ret = __cw1200_reg_write(priv, addr, buf, buf_len, 0);
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	return ret;
}