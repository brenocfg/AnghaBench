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
struct sht15_data {int /*<<< orphan*/  sck; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHT15_TSCKH ; 
 int /*<<< orphan*/  SHT15_TSCKL ; 
 int /*<<< orphan*/  gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sht15_read_byte(struct sht15_data *data)
{
	int i;
	u8 byte = 0;

	for (i = 0; i < 8; ++i) {
		byte <<= 1;
		gpiod_set_value(data->sck, 1);
		ndelay(SHT15_TSCKH);
		byte |= !!gpiod_get_value(data->data);
		gpiod_set_value(data->sck, 0);
		ndelay(SHT15_TSCKL);
	}
	return byte;
}