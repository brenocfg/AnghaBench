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
struct ad2s1210_state {int /*<<< orphan*/ * tx; int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CONFIG ; 
 int /*<<< orphan*/  ad2s1210_set_mode (int /*<<< orphan*/ ,struct ad2s1210_state*) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad2s1210_config_write(struct ad2s1210_state *st, u8 data)
{
	int ret;

	ad2s1210_set_mode(MOD_CONFIG, st);
	st->tx[0] = data;
	ret = spi_write(st->sdev, st->tx, 1);
	if (ret < 0)
		return ret;

	return 0;
}