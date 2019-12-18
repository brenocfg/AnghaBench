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
struct sdio_data {void* sys_sdio_irq_thd; } ;
struct dvobj_priv {struct sdio_data intf_data; } ;

/* Variables and functions */

inline void rtw_sdio_set_irq_thd(struct dvobj_priv *dvobj, void *thd_hdl)
{
	struct sdio_data *sdio_data = &dvobj->intf_data;

	sdio_data->sys_sdio_irq_thd = thd_hdl;
}