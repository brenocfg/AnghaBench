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
struct gpio_chip {int bgpio_bits; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bgpio_read16 ; 
 int /*<<< orphan*/  bgpio_read16be ; 
 int /*<<< orphan*/  bgpio_read32 ; 
 int /*<<< orphan*/  bgpio_read32be ; 
 int /*<<< orphan*/  bgpio_read64 ; 
 int /*<<< orphan*/  bgpio_read8 ; 
 int /*<<< orphan*/  bgpio_write16 ; 
 int /*<<< orphan*/  bgpio_write16be ; 
 int /*<<< orphan*/  bgpio_write32 ; 
 int /*<<< orphan*/  bgpio_write32be ; 
 int /*<<< orphan*/  bgpio_write64 ; 
 int /*<<< orphan*/  bgpio_write8 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 

__attribute__((used)) static int bgpio_setup_accessors(struct device *dev,
				 struct gpio_chip *gc,
				 bool byte_be)
{

	switch (gc->bgpio_bits) {
	case 8:
		gc->read_reg	= bgpio_read8;
		gc->write_reg	= bgpio_write8;
		break;
	case 16:
		if (byte_be) {
			gc->read_reg	= bgpio_read16be;
			gc->write_reg	= bgpio_write16be;
		} else {
			gc->read_reg	= bgpio_read16;
			gc->write_reg	= bgpio_write16;
		}
		break;
	case 32:
		if (byte_be) {
			gc->read_reg	= bgpio_read32be;
			gc->write_reg	= bgpio_write32be;
		} else {
			gc->read_reg	= bgpio_read32;
			gc->write_reg	= bgpio_write32;
		}
		break;
#if BITS_PER_LONG >= 64
	case 64:
		if (byte_be) {
			dev_err(dev,
				"64 bit big endian byte order unsupported\n");
			return -EINVAL;
		} else {
			gc->read_reg	= bgpio_read64;
			gc->write_reg	= bgpio_write64;
		}
		break;
#endif /* BITS_PER_LONG >= 64 */
	default:
		dev_err(dev, "unsupported data width %u bits\n", gc->bgpio_bits);
		return -EINVAL;
	}

	return 0;
}