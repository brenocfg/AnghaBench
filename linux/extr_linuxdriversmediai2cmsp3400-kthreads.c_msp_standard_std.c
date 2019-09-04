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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct TYPE_2__ {int retval; int /*<<< orphan*/  std; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 TYPE_1__* msp_stdlist ; 

__attribute__((used)) static v4l2_std_id msp_standard_std(int std)
{
	int i;

	for (i = 0; msp_stdlist[i].name != NULL; i++)
		if (msp_stdlist[i].retval == std)
			return msp_stdlist[i].std;
	return V4L2_STD_ALL;
}