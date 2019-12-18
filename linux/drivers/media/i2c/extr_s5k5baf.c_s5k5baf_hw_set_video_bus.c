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
typedef  scalar_t__ u16 ;
struct s5k5baf {scalar_t__ bus_type; int /*<<< orphan*/  nlanes; } ;

/* Variables and functions */
 scalar_t__ EN_PACKETS_CSI2 ; 
 int /*<<< orphan*/  REG_OIF_EN_MIPI_LANES ; 
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int s5k5baf_clear_error (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_write_seq (struct s5k5baf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int s5k5baf_hw_set_video_bus(struct s5k5baf *state)
{
	u16 en_pkts;

	if (state->bus_type == V4L2_MBUS_CSI2_DPHY)
		en_pkts = EN_PACKETS_CSI2;
	else
		en_pkts = 0;

	s5k5baf_write_seq(state, REG_OIF_EN_MIPI_LANES,
			  state->nlanes, en_pkts, 1);

	return s5k5baf_clear_error(state);
}