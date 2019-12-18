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
typedef  int /*<<< orphan*/  u32 ;
struct sja1105_port_status_hl1 {int n_n664err; int n_vlanerr; int n_unreleased; int n_sizeerr; int n_crcerr; int n_vlnotfound; int n_ctpolerr; int n_polerr; int n_rxfrmsh; int n_rxfrm; int n_rxbytesh; int n_rxbyte; int n_txfrmsh; int n_txfrm; int n_txbytesh; int n_txbyte; } ;

/* Variables and functions */
 int /*<<< orphan*/  sja1105_unpack (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sja1105_port_status_hl1_unpack(void *buf,
			       struct sja1105_port_status_hl1 *status)
{
	/* Make pointer arithmetic work on 4 bytes */
	u32 *p = buf;

	sja1105_unpack(p + 0xF, &status->n_n664err,    31,  0, 4);
	sja1105_unpack(p + 0xE, &status->n_vlanerr,    31,  0, 4);
	sja1105_unpack(p + 0xD, &status->n_unreleased, 31,  0, 4);
	sja1105_unpack(p + 0xC, &status->n_sizeerr,    31,  0, 4);
	sja1105_unpack(p + 0xB, &status->n_crcerr,     31,  0, 4);
	sja1105_unpack(p + 0xA, &status->n_vlnotfound, 31,  0, 4);
	sja1105_unpack(p + 0x9, &status->n_ctpolerr,   31,  0, 4);
	sja1105_unpack(p + 0x8, &status->n_polerr,     31,  0, 4);
	sja1105_unpack(p + 0x7, &status->n_rxfrmsh,    31,  0, 4);
	sja1105_unpack(p + 0x6, &status->n_rxfrm,      31,  0, 4);
	sja1105_unpack(p + 0x5, &status->n_rxbytesh,   31,  0, 4);
	sja1105_unpack(p + 0x4, &status->n_rxbyte,     31,  0, 4);
	sja1105_unpack(p + 0x3, &status->n_txfrmsh,    31,  0, 4);
	sja1105_unpack(p + 0x2, &status->n_txfrm,      31,  0, 4);
	sja1105_unpack(p + 0x1, &status->n_txbytesh,   31,  0, 4);
	sja1105_unpack(p + 0x0, &status->n_txbyte,     31,  0, 4);
	status->n_rxfrm  += status->n_rxfrmsh  << 32;
	status->n_rxbyte += status->n_rxbytesh << 32;
	status->n_txfrm  += status->n_txfrmsh  << 32;
	status->n_txbyte += status->n_txbytesh << 32;
}