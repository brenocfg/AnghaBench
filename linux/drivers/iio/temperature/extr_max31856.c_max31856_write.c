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
struct max31856_data {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int MAX31856_RD_WR_BIT ; 
 int spi_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int max31856_write(struct max31856_data *data, u8 reg,
			  unsigned int val)
{
	u8 buf[2];

	buf[0] = reg | (MAX31856_RD_WR_BIT);
	buf[1] = val;

	return spi_write(data->spi, buf, 2);
}