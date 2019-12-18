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
struct dvobj_priv {struct adapter* padapters; } ;
struct TYPE_2__ {char* ifname; } ;
struct adapter {TYPE_1__ registrypriv; struct dvobj_priv* dvobj; } ;

/* Variables and functions */
 int _rtw_drv_register_netdev (struct adapter*,char*) ; 

int rtw_drv_register_netdev(struct adapter *if1)
{
	struct dvobj_priv *dvobj = if1->dvobj;
	struct adapter *padapter = dvobj->padapters;
	char *name = if1->registrypriv.ifname;

	return _rtw_drv_register_netdev(padapter, name);
}