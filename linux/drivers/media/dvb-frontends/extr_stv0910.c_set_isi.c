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
typedef  int u32 ;
struct stv {scalar_t__ regoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALGOSWRST ; 
 int /*<<< orphan*/  FILTER_EN ; 
 int /*<<< orphan*/  FORCE_CONTINUOUS ; 
 int NO_STREAM_ID_FILTER ; 
 scalar_t__ RSTV0910_P2_ISIBITENA ; 
 scalar_t__ RSTV0910_P2_ISIENTRY ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TSOUT_NOSYNC ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,int) ; 

__attribute__((used)) static void set_isi(struct stv *state, u32 isi)
{
	if (isi == NO_STREAM_ID_FILTER)
		return;
	if (isi == 0x80000000) {
		SET_FIELD(FORCE_CONTINUOUS, 1);
		SET_FIELD(TSOUT_NOSYNC, 1);
	} else {
		SET_FIELD(FILTER_EN, 1);
		write_reg(state, RSTV0910_P2_ISIENTRY + state->regoff,
			  isi & 0xff);
		write_reg(state, RSTV0910_P2_ISIBITENA + state->regoff, 0xff);
	}
	SET_FIELD(ALGOSWRST, 1);
	SET_FIELD(ALGOSWRST, 0);
}