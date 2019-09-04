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
typedef  int uint8_t ;
struct pipe_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int i2c_write (struct pipe_ctx*,int,int*,int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void write_i2c_redriver_setting(
		struct pipe_ctx *pipe_ctx,
		bool is_over_340mhz)
{
	uint8_t slave_address = (0xF0 >> 1);
	uint8_t buffer[16];
	bool i2c_success = false;

	memset(&buffer, 0, sizeof(buffer));

	// Program Slave Address for tuning single integrity
	buffer[3] = 0x4E;
	buffer[4] = 0x4E;
	buffer[5] = 0x4E;
	buffer[6] = is_over_340mhz ? 0x4E : 0x4A;

	i2c_success = i2c_write(pipe_ctx, slave_address,
					buffer, sizeof(buffer));

	if (!i2c_success)
		/* Write failure */
		ASSERT(i2c_success);
}