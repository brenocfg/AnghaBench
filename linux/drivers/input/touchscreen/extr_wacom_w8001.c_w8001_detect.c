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
struct w8001 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W8001_CMD_STOP ; 
 int /*<<< orphan*/  msleep (int) ; 
 int w8001_command (struct w8001*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int w8001_detect(struct w8001 *w8001)
{
	int error;

	error = w8001_command(w8001, W8001_CMD_STOP, false);
	if (error)
		return error;

	msleep(250);	/* wait 250ms before querying the device */

	return 0;
}