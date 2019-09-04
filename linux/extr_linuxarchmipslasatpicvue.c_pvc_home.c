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
 int /*<<< orphan*/  HOME_CMD ; 
 int /*<<< orphan*/  MODE_INST ; 
 int /*<<< orphan*/  pvc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pvc_home(void)
{
	pvc_write(HOME_CMD, MODE_INST);
}