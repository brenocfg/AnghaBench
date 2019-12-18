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
typedef  int v4l2_std_id ;
struct pvr2_ctrl {int dummy; } ;

/* Variables and functions */
 int pvr2_std_str_to_id (int*,char const*,unsigned int) ; 

__attribute__((used)) static int ctrl_std_sym_to_val(struct pvr2_ctrl *cptr,
			       const char *bufPtr,unsigned int bufSize,
			       int *mskp,int *valp)
{
	int ret;
	v4l2_std_id id;
	ret = pvr2_std_str_to_id(&id,bufPtr,bufSize);
	if (ret < 0) return ret;
	if (mskp) *mskp = id;
	if (valp) *valp = id;
	return 0;
}