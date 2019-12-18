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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DCB_APP_IDTYPE_ETHTYPE ; 
 int __cxgb4_getapp (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb4_getapp(struct net_device *dev, u8 app_idtype, u16 app_id)
{
	/* Convert app_idtype to firmware format before querying */
	return __cxgb4_getapp(dev, app_idtype == DCB_APP_IDTYPE_ETHTYPE ?
			      app_idtype : 3, app_id, 0);
}