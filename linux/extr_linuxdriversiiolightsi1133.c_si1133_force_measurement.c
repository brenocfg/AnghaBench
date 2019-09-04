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
struct si1133_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1133_CMD_FORCE ; 
 int si1133_command (struct si1133_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1133_force_measurement(struct si1133_data *data)
{
	return si1133_command(data, SI1133_CMD_FORCE);
}