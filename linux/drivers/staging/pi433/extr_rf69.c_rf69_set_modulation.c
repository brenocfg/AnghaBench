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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  enum modulation { ____Placeholder_modulation } modulation ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  DATAMODUL_MODULATION_TYPE_FSK 131 
#define  DATAMODUL_MODULATION_TYPE_OOK 130 
 int EINVAL ; 
#define  FSK 129 
 int /*<<< orphan*/  MASK_DATAMODUL_MODULATION_TYPE ; 
#define  OOK 128 
 int /*<<< orphan*/  REG_DATAMODUL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int rf69_read_mod_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ unlikely (int) ; 

int rf69_set_modulation(struct spi_device *spi, enum modulation modulation)
{
	static const u8 modulation_map[] = {
		[OOK] = DATAMODUL_MODULATION_TYPE_OOK,
		[FSK] = DATAMODUL_MODULATION_TYPE_FSK,
	};

	if (unlikely(modulation >= ARRAY_SIZE(modulation_map))) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	return rf69_read_mod_write(spi, REG_DATAMODUL,
				   MASK_DATAMODUL_MODULATION_TYPE,
				   modulation_map[modulation]);
}