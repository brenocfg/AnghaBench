#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;
struct mux_control {TYPE_2__* chip; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADGS1408_DISABLE ; 
 int /*<<< orphan*/  ADGS1408_MUX (int) ; 
 int /*<<< orphan*/  ADGS1408_SW_DATA ; 
 int MUX_IDLE_DISCONNECT ; 
 int adgs1408_spi_reg_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adgs1408_set(struct mux_control *mux, int state)
{
	struct spi_device *spi = to_spi_device(mux->chip->dev.parent);
	u8 reg;

	if (state == MUX_IDLE_DISCONNECT)
		reg = ADGS1408_DISABLE;
	else
		reg = ADGS1408_MUX(state);

	return adgs1408_spi_reg_write(spi, ADGS1408_SW_DATA, reg);
}