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
typedef  unsigned int u8 ;
struct spi_transfer {int dummy; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;
struct ds1305 {struct spi_device* spi; } ;

/* Variables and functions */
 unsigned int DS1305_NVRAM ; 
 unsigned int DS1305_WRITE ; 
 int /*<<< orphan*/  msg_init (struct spi_message*,struct spi_transfer*,unsigned int*,size_t,void*,int /*<<< orphan*/ *) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int ds1305_nvram_write(void *priv, unsigned int off, void *buf,
			      size_t count)
{
	struct ds1305		*ds1305 = priv;
	struct spi_device	*spi = ds1305->spi;
	u8			addr;
	struct spi_message	m;
	struct spi_transfer	x[2];

	addr = (DS1305_WRITE | DS1305_NVRAM) + off;
	msg_init(&m, x, &addr, count, buf, NULL);

	return spi_sync(spi, &m);
}