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
 int EIGHT_BYTE ; 
 int FUNC_SET_CMD ; 
 int LARGE_FONT ; 
 int /*<<< orphan*/  MODE_INST ; 
 int TWO_LINES ; 
 int /*<<< orphan*/  pvc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvc_funcset(u8 cmd)
{
	pvc_write(FUNC_SET_CMD | (cmd & (EIGHT_BYTE|TWO_LINES|LARGE_FONT)),
		  MODE_INST);
}