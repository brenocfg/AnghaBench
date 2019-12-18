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
struct TYPE_2__ {int (* sym_to_val ) (struct pvr2_ctrl*,char const*,unsigned int,int*,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct pvr2_ctrl*,char const*,unsigned int,int*,int*) ; 

int pvr2_ctrl_custom_sym_to_value(struct pvr2_ctrl *cptr,
				  const char *buf,unsigned int len,
				  int *maskptr,int *valptr)
{
	if (!cptr) return -EINVAL;
	if (!cptr->info->sym_to_val) return -EINVAL;
	return cptr->info->sym_to_val(cptr,buf,len,maskptr,valptr);
}