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
struct sja1105_spi_message {int /*<<< orphan*/  address; int /*<<< orphan*/  read_count; int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int SJA1105_SIZE_SPI_MSG_HEADER ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  sja1105_pack (void*,int /*<<< orphan*/ *,int,int,int const) ; 

__attribute__((used)) static void
sja1105_spi_message_pack(void *buf, const struct sja1105_spi_message *msg)
{
	const int size = SJA1105_SIZE_SPI_MSG_HEADER;

	memset(buf, 0, size);

	sja1105_pack(buf, &msg->access,     31, 31, size);
	sja1105_pack(buf, &msg->read_count, 30, 25, size);
	sja1105_pack(buf, &msg->address,    24,  4, size);
}