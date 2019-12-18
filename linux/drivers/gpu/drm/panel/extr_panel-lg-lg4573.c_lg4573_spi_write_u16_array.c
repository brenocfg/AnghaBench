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
typedef  int /*<<< orphan*/  u16 ;
struct lg4573 {int dummy; } ;

/* Variables and functions */
 int lg4573_spi_write_u16 (struct lg4573*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int lg4573_spi_write_u16_array(struct lg4573 *ctx, const u16 *buffer,
				      unsigned int count)
{
	unsigned int i;
	int ret;

	for (i = 0; i < count; i++) {
		ret = lg4573_spi_write_u16(ctx, buffer[i]);
		if (ret)
			return ret;
	}

	return 0;
}