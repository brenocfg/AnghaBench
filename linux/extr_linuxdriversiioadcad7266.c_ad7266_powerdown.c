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
struct TYPE_2__ {int /*<<< orphan*/ * sample; } ;
struct ad7266_state {TYPE_1__ data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int spi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad7266_powerdown(struct ad7266_state *st)
{
	/* Any read with < 2 bytes will powerdown the device */
	return spi_read(st->spi, &st->data.sample[0], 1);
}