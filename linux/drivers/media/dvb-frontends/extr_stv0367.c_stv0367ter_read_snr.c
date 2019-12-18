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
typedef  int u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int stv0367ter_snr_readreg (struct dvb_frontend*) ; 

__attribute__((used)) static int stv0367ter_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	u32 snrval = stv0367ter_snr_readreg(fe);

	*snr = snrval / 1000;

	return 0;
}