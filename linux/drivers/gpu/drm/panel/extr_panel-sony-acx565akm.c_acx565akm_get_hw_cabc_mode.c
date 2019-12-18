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
struct acx565akm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID_CMD_READ_CABC ; 
 int /*<<< orphan*/  acx565akm_read (struct acx565akm_panel*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static unsigned int acx565akm_get_hw_cabc_mode(struct acx565akm_panel *lcd)
{
	u8 cabc_ctrl;

	acx565akm_read(lcd, MIPID_CMD_READ_CABC, &cabc_ctrl, 1);
	return cabc_ctrl & 3;
}