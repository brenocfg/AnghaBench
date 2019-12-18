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
typedef  int /*<<< orphan*/  u8 ;
struct ps2dev {int dummy; } ;

/* Variables and functions */
 int __ps2_command (struct ps2dev*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ps2_begin_command (struct ps2dev*) ; 
 int /*<<< orphan*/  ps2_end_command (struct ps2dev*) ; 

int ps2_command(struct ps2dev *ps2dev, u8 *param, unsigned int command)
{
	int rc;

	ps2_begin_command(ps2dev);
	rc = __ps2_command(ps2dev, param, command);
	ps2_end_command(ps2dev);

	return rc;
}