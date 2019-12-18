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
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  enum packet_format { ____Placeholder_packet_format } packet_format ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MASK_PACKETCONFIG1_PACKET_FORMAT_VARIABLE ; 
 int /*<<< orphan*/  REG_PACKETCONFIG1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
#define  packet_length_fix 129 
#define  packet_length_var 128 
 int rf69_clear_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rf69_set_packet_format(struct spi_device *spi,
			   enum packet_format packet_format)
{
	switch (packet_format) {
	case packet_length_var:
		return rf69_set_bit(spi, REG_PACKETCONFIG1,
				    MASK_PACKETCONFIG1_PACKET_FORMAT_VARIABLE);
	case packet_length_fix:
		return rf69_clear_bit(spi, REG_PACKETCONFIG1,
				      MASK_PACKETCONFIG1_PACKET_FORMAT_VARIABLE);
	default:
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}
}