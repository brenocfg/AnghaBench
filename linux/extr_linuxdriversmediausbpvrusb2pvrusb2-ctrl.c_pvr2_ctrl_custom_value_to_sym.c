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
struct pvr2_ctrl {TYPE_1__* info; } ;
struct TYPE_2__ {int (* val_to_sym ) (struct pvr2_ctrl*,int,int,char*,unsigned int,unsigned int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct pvr2_ctrl*,int,int,char*,unsigned int,unsigned int*) ; 

int pvr2_ctrl_custom_value_to_sym(struct pvr2_ctrl *cptr,
				  int mask,int val,
				  char *buf,unsigned int maxlen,
				  unsigned int *len)
{
	if (!cptr) return -EINVAL;
	if (!cptr->info->val_to_sym) return -EINVAL;
	return cptr->info->val_to_sym(cptr,mask,val,buf,maxlen,len);
}