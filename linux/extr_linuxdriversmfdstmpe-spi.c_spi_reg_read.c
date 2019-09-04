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
struct stmpe {struct spi_device* client; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int READ_CMD ; 
 int spi_w8r16 (struct spi_device*,int) ; 

__attribute__((used)) static int spi_reg_read(struct stmpe *stmpe, u8 reg)
{
	struct spi_device *spi = stmpe->client;
	int status = spi_w8r16(spi, reg | READ_CMD);

	return (status < 0) ? status : status >> 8;
}