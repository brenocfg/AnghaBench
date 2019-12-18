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
typedef  scalar_t__ u8 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRO_SET_CMD ; 
 int ms_write_bytes (struct rtsx_chip*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static int ms_send_cmd(struct rtsx_chip *chip, u8 cmd, u8 cfg)
{
	u8 data[2];

	data[0] = cmd;
	data[1] = 0;

	return ms_write_bytes(chip, PRO_SET_CMD, 1, cfg, data, 1);
}