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
 int CUR_BLINK ; 
 int CUR_ON ; 
 int DISP_CNT_CMD ; 
 int DISP_ON ; 
 int /*<<< orphan*/  MODE_INST ; 
 int /*<<< orphan*/  pvc_write (int,int /*<<< orphan*/ ) ; 

void pvc_dispcnt(u8 cmd)
{
	pvc_write(DISP_CNT_CMD | (cmd & (DISP_ON|CUR_ON|CUR_BLINK)), MODE_INST);
}