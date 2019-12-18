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
typedef  int /*<<< orphan*/  wmem ;
struct wiimote_data {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int wiimote_cmd_write (struct wiimote_data*,int,int*,int) ; 

__attribute__((used)) static int wiimote_cmd_init_mp(struct wiimote_data *wdata)
{
	__u8 wmem;
	int ret;

	/* initialize MP */
	wmem = 0x55;
	ret = wiimote_cmd_write(wdata, 0xa600f0, &wmem, sizeof(wmem));
	if (ret)
		return ret;

	/* disable default encryption */
	wmem = 0x0;
	ret = wiimote_cmd_write(wdata, 0xa600fb, &wmem, sizeof(wmem));
	if (ret)
		return ret;

	return 0;
}