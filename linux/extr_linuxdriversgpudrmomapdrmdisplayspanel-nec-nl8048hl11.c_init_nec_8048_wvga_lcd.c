#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dat; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* nec_8048_init_seq ; 
 int /*<<< orphan*/  nec_8048_spi_send (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int init_nec_8048_wvga_lcd(struct spi_device *spi)
{
	unsigned int i;
	/* Initialization Sequence */
	/* nec_8048_spi_send(spi, REG, VAL) */
	for (i = 0; i < (ARRAY_SIZE(nec_8048_init_seq) - 1); i++)
		nec_8048_spi_send(spi, nec_8048_init_seq[i].addr,
				nec_8048_init_seq[i].dat);
	udelay(20);
	nec_8048_spi_send(spi, nec_8048_init_seq[i].addr,
				nec_8048_init_seq[i].dat);
	return 0;
}