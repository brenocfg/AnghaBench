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
typedef  int u8 ;

/* Variables and functions */
 int SNS0_EQUIPMENT_CHECK ; 
 int SNS1_PERM_ERR ; 
 int SNS1_WRITE_INHIBITED ; 

__attribute__((used)) static int dasd_ese_oos_cond(u8 *sense)
{
	return sense[0] & SNS0_EQUIPMENT_CHECK &&
		sense[1] & SNS1_PERM_ERR &&
		sense[1] & SNS1_WRITE_INHIBITED &&
		sense[25] == 0x01;
}