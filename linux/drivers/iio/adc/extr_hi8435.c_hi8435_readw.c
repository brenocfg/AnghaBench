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
struct hi8435_priv {int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  HI8435_READ_OPCODE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int spi_write_then_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hi8435_readw(struct hi8435_priv *priv, u8 reg, u16 *val)
{
	int ret;
	__be16 be_val;

	reg |= HI8435_READ_OPCODE;
	ret = spi_write_then_read(priv->spi, &reg, 1, &be_val, 2);
	*val = be16_to_cpu(be_val);

	return ret;
}