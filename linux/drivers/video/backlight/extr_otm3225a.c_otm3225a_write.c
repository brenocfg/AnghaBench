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
struct spi_device {int dummy; } ;
struct otm3225a_spi_instruction {unsigned char reg; int value; scalar_t__ delay; } ;

/* Variables and functions */
 unsigned char OTM3225A_DATA_REG ; 
 unsigned char OTM3225A_INDEX_REG ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  spi_write (struct spi_device*,unsigned char*,int) ; 

__attribute__((used)) static void otm3225a_write(struct spi_device *spi,
			   struct otm3225a_spi_instruction *instruction,
			   unsigned int count)
{
	unsigned char buf[3];

	while (count--) {
		/* address register using index register */
		buf[0] = OTM3225A_INDEX_REG;
		buf[1] = 0x00;
		buf[2] = instruction->reg;
		spi_write(spi, buf, 3);

		/* write data to addressed register */
		buf[0] = OTM3225A_DATA_REG;
		buf[1] = (instruction->value >> 8) & 0xff;
		buf[2] = instruction->value & 0xff;
		spi_write(spi, buf, 3);

		/* execute delay if any */
		if (instruction->delay)
			msleep(instruction->delay);
		instruction++;
	}
}