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
typedef  int /*<<< orphan*/  vrc4173_socket_t ;
typedef  int uint8_t ;
struct TYPE_3__ {int Vpp; int Vcc; int flags; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 int CARD_OUT_EN ; 
 int CARD_REST0 ; 
 int CARD_TYPE_IO ; 
 int EINVAL ; 
 int /*<<< orphan*/  INT_GEN_CNT ; 
 int /*<<< orphan*/  PWR_CNT ; 
 int SS_IOCARD ; 
 int SS_OUTPUT_ENA ; 
 int SS_RESET ; 
 int /*<<< orphan*/ * cardu_sockets ; 
 int exca_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int set_Vcc_value (int) ; 
 int set_Vpp_value (int) ; 

__attribute__((used)) static int cardu_set_socket(unsigned int sock, socket_state_t *state)
{
	vrc4173_socket_t *socket = &cardu_sockets[sock];
	uint8_t val;

	if (((state->Vpp == 33) || (state->Vpp == 50)) && (state->Vpp != state->Vcc))
			return -EINVAL;

	val = set_Vcc_value(state->Vcc);
	val |= set_Vpp_value(state->Vpp);
	if (state->flags & SS_OUTPUT_ENA) val |= CARD_OUT_EN;
	exca_writeb(socket, PWR_CNT, val);

	val = exca_readb(socket, INT_GEN_CNT) & CARD_REST0;
	if (state->flags & SS_RESET) val &= ~CARD_REST0;
	else val |= CARD_REST0;
	if (state->flags & SS_IOCARD) val |= CARD_TYPE_IO;
	exca_writeb(socket, INT_GEN_CNT, val);

	return 0;
}