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
struct ad9834_state {int /*<<< orphan*/  msg; int /*<<< orphan*/  spi; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD9834_PHASE_BITS ; 
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned long) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad9834_write_phase(struct ad9834_state *st,
			      unsigned long addr, unsigned long phase)
{
	if (phase > BIT(AD9834_PHASE_BITS))
		return -EINVAL;
	st->data = cpu_to_be16(addr | phase);

	return spi_sync(st->spi, &st->msg);
}