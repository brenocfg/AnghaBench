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
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int FIFO_SIZE ; 
 int REG_FIFO ; 
 int WRITE_BIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 int spi_write (struct spi_device*,int*,unsigned int) ; 

int rf69_write_fifo(struct spi_device *spi, u8 *buffer, unsigned int size)
{
#ifdef DEBUG_FIFO_ACCESS
	int i;
#endif
	u8 local_buffer[FIFO_SIZE + 1];

	if (size > FIFO_SIZE) {
		dev_dbg(&spi->dev,
			"read fifo: passed in buffer bigger then internal buffer\n");
		return -EMSGSIZE;
	}

	local_buffer[0] = REG_FIFO | WRITE_BIT;
	memcpy(&local_buffer[1], buffer, size);

#ifdef DEBUG_FIFO_ACCESS
	for (i = 0; i < size; i++)
		dev_dbg(&spi->dev, "0x%x\n", buffer[i]);
#endif

	return spi_write(spi, local_buffer, size + 1);
}