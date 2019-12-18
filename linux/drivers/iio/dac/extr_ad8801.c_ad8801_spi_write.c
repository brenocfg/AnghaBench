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
typedef  unsigned char u8 ;
struct ad8801_state {int /*<<< orphan*/  data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 unsigned char AD8801_CFG_ADDR_OFFSET ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned char) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad8801_spi_write(struct ad8801_state *state,
	u8 channel, unsigned char value)
{
	state->data = cpu_to_be16((channel << AD8801_CFG_ADDR_OFFSET) | value);
	return spi_write(state->spi, &state->data, sizeof(state->data));
}