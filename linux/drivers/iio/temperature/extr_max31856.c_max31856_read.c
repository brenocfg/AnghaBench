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
struct max31856_data {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int spi_write_then_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int max31856_read(struct max31856_data *data, u8 reg,
			 u8 val[], unsigned int read_size)
{
	return spi_write_then_read(data->spi, &reg, 1, val, read_size);
}