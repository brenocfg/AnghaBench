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
typedef  int u16 ;
struct spi_device {int dummy; } ;
struct max5481_data {int* msg; struct spi_device* spi; } ;

/* Variables and functions */
 int EIO ; 
#define  MAX5481_COPY_AB_TO_NV 130 
#define  MAX5481_COPY_NV_TO_AB 129 
#define  MAX5481_WRITE_WIPER 128 
 int spi_write (struct spi_device*,int*,int) ; 

__attribute__((used)) static int max5481_write_cmd(struct max5481_data *data, u8 cmd, u16 val)
{
	struct spi_device *spi = data->spi;

	data->msg[0] = cmd;

	switch (cmd) {
	case MAX5481_WRITE_WIPER:
		data->msg[1] = val >> 2;
		data->msg[2] = (val & 0x3) << 6;
		return spi_write(spi, data->msg, 3);

	case MAX5481_COPY_AB_TO_NV:
	case MAX5481_COPY_NV_TO_AB:
		return spi_write(spi, data->msg, 1);

	default:
		return -EIO;
	}
}