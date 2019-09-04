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

/* Variables and functions */
 int ETIME ; 
 int PVC_BUSY ; 
 int TIMEOUT ; 
 int pvc_read_data () ; 

__attribute__((used)) static int pvc_wait(void)
{
	int i = TIMEOUT;
	int err = 0;

	while ((pvc_read_data() & PVC_BUSY) && i)
		i--;
	if (i == 0)
		err = -ETIME;

	return err;
}