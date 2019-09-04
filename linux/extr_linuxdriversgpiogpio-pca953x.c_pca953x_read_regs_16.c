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
typedef  int /*<<< orphan*/  u16 ;
struct pca953x_chip {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca953x_read_regs_16(struct pca953x_chip *chip, int reg, u8 *val)
{
	int ret;

	ret = i2c_smbus_read_word_data(chip->client, reg << 1);
	put_unaligned(ret, (u16 *)val);

	return ret;
}