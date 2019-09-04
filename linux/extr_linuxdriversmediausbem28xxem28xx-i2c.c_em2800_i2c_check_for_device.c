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
struct em28xx {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int em2800_i2c_recv_bytes (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int em2800_i2c_check_for_device(struct em28xx *dev, u8 addr)
{
	u8 buf;
	int ret;

	ret = em2800_i2c_recv_bytes(dev, addr, &buf, 1);
	if (ret == 1)
		return 0;
	return (ret < 0) ? ret : -EIO;
}