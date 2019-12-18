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
struct mipi_dbi {int /*<<< orphan*/  read_commands; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int mipi_dbi_command_buf (struct mipi_dbi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mipi_dbi_command_is_read (struct mipi_dbi*,int /*<<< orphan*/ ) ; 

int mipi_dbi_command_read(struct mipi_dbi *dbi, u8 cmd, u8 *val)
{
	if (!dbi->read_commands)
		return -EACCES;

	if (!mipi_dbi_command_is_read(dbi, cmd))
		return -EINVAL;

	return mipi_dbi_command_buf(dbi, cmd, val, 1);
}