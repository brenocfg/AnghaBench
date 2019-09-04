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
struct sht15_data {int /*<<< orphan*/  sck; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHT15_TSCKH ; 
 int /*<<< orphan*/  SHT15_TSCKL ; 
 int /*<<< orphan*/  SHT15_TSU ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sht15_send_bit(struct sht15_data *data, int val)
{
	gpiod_set_value(data->data, val);
	ndelay(SHT15_TSU);
	gpiod_set_value(data->sck, 1);
	ndelay(SHT15_TSCKH);
	gpiod_set_value(data->sck, 0);
	ndelay(SHT15_TSCKL); /* clock low time */
}