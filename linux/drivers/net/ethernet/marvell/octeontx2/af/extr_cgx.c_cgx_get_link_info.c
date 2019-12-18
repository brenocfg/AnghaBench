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
struct cgx_link_user_info {int dummy; } ;
struct lmac {struct cgx_link_user_info link_info; } ;

/* Variables and functions */
 int ENODEV ; 
 struct lmac* lmac_pdata (int,void*) ; 

int cgx_get_link_info(void *cgxd, int lmac_id,
		      struct cgx_link_user_info *linfo)
{
	struct lmac *lmac = lmac_pdata(lmac_id, cgxd);

	if (!lmac)
		return -ENODEV;

	*linfo = lmac->link_info;
	return 0;
}