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
struct hi8435_priv {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  HI8435_READ_OPCODE ; 
 int spi_write_then_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hi8435_readb(struct hi8435_priv *priv, u8 reg, u8 *val)
{
	reg |= HI8435_READ_OPCODE;
	return spi_write_then_read(priv->spi, &reg, 1, val, 1);
}