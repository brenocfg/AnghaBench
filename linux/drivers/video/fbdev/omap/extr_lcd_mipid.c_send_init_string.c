#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  data_lines; } ;
struct mipid_device {TYPE_1__ panel; } ;
typedef  int /*<<< orphan*/  initpar ;

/* Variables and functions */
 int /*<<< orphan*/  mipid_write (struct mipid_device*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_data_lines (struct mipid_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_init_string(struct mipid_device *md)
{
	u16 initpar[] = { 0x0102, 0x0100, 0x0100 };

	mipid_write(md, 0xc2, (u8 *)initpar, sizeof(initpar));
	set_data_lines(md, md->panel.data_lines);
}