#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ffen; scalar_t__ trm; scalar_t__ spi_en; int /*<<< orphan*/  cs; scalar_t__ wl; } ;
union kp_spi_config {int /*<<< orphan*/  reg; TYPE_1__ bitfield; } ;
struct spi_device {struct kp_spi_controller_state* controller_state; int /*<<< orphan*/  chip_select; scalar_t__ bits_per_word; int /*<<< orphan*/  master; } ;
struct kp_spi_controller_state {int conf_cache; int /*<<< orphan*/  base; } ;
struct kp_spi {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KP_SPI_REG_CONFIG ; 
 int /*<<< orphan*/  kp_spi_write_reg (struct kp_spi_controller_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kp_spi_controller_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct kp_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kp_spi_setup(struct spi_device *spidev)
{
	union kp_spi_config sc;
	struct kp_spi *kpspi = spi_master_get_devdata(spidev->master);
	struct kp_spi_controller_state *cs;

	/* setup controller state */
	cs = spidev->controller_state;
	if (!cs) {
		cs = kzalloc(sizeof(*cs), GFP_KERNEL);
		if (!cs)
			return -ENOMEM;
		cs->base = kpspi->base;
		cs->conf_cache = -1;
		spidev->controller_state = cs;
	}

	/* set config register */
	sc.bitfield.wl = spidev->bits_per_word - 1;
	sc.bitfield.cs = spidev->chip_select;
	sc.bitfield.spi_en = 0;
	sc.bitfield.trm = 0;
	sc.bitfield.ffen = 0;
	kp_spi_write_reg(spidev->controller_state, KP_SPI_REG_CONFIG, sc.reg);
	return 0;
}