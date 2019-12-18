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
struct sca3000_state {int /*<<< orphan*/ * tx; int /*<<< orphan*/  us; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_WRITE_REG (int /*<<< orphan*/ ) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sca3000_write_reg(struct sca3000_state *st, u8 address, u8 val)
{
	st->tx[0] = SCA3000_WRITE_REG(address);
	st->tx[1] = val;
	return spi_write(st->us, st->tx, 2);
}