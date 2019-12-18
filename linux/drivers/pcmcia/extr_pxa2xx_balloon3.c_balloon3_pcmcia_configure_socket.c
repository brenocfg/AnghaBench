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
struct soc_pcmcia_socket {int dummy; } ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 scalar_t__ BALLOON3_CF_CONTROL_REG ; 
 int /*<<< orphan*/  BALLOON3_CF_RESET ; 
 int /*<<< orphan*/  BALLOON3_FPGA_SETnCLR ; 
 int SS_RESET ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int balloon3_pcmcia_configure_socket(struct soc_pcmcia_socket *skt,
				       const socket_state_t *state)
{
	__raw_writew(BALLOON3_CF_RESET, BALLOON3_CF_CONTROL_REG +
			((state->flags & SS_RESET) ?
			BALLOON3_FPGA_SETnCLR : 0));
	return 0;
}