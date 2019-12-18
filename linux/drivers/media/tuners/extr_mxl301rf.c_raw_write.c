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
struct mxl301rf_state {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int raw_write(struct mxl301rf_state *state, const u8 *buf, int len)
{
	int ret;

	ret = i2c_master_send(state->i2c, buf, len);
	if (ret >= 0 && ret < len)
		ret = -EIO;
	return (ret == len) ? 0 : ret;
}