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
struct spi_nor {int dummy; } ;

/* Variables and functions */
 int cqspi_command_write (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int cqspi_set_protocol (struct spi_nor*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cqspi_write_reg(struct spi_nor *nor, u8 opcode, u8 *buf, int len)
{
	int ret;

	ret = cqspi_set_protocol(nor, 0);
	if (!ret)
		ret = cqspi_command_write(nor, opcode, buf, len);

	return ret;
}