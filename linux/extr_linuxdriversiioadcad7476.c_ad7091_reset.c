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
struct ad7476_state {int /*<<< orphan*/  data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ad7091_reset(struct ad7476_state *st)
{
	/* Any transfers with 8 scl cycles will reset the device */
	spi_read(st->spi, st->data, 1);
}