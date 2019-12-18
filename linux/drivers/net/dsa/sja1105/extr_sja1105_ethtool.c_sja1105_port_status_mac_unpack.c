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
struct sja1105_port_status_mac {int /*<<< orphan*/  agedrp; int /*<<< orphan*/  spcerr; int /*<<< orphan*/  drpnona664err; int /*<<< orphan*/  policeerr; int /*<<< orphan*/  bagdrop; int /*<<< orphan*/  lendrop; int /*<<< orphan*/  portdrop; int /*<<< orphan*/  ageprior; int /*<<< orphan*/  spcprior; int /*<<< orphan*/  pcfbagdrop; int /*<<< orphan*/  domerr; int /*<<< orphan*/  intcyov; int /*<<< orphan*/  invtyp; int /*<<< orphan*/  memerr; int /*<<< orphan*/  memov; int /*<<< orphan*/  nomaster; int /*<<< orphan*/  priorerr; int /*<<< orphan*/  tctimeout; int /*<<< orphan*/  sizeerr; int /*<<< orphan*/  typeerr; int /*<<< orphan*/  n_miierr; int /*<<< orphan*/  n_alignerr; int /*<<< orphan*/  n_soferr; int /*<<< orphan*/  n_runt; } ;

/* Variables and functions */
 int /*<<< orphan*/  sja1105_unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void
sja1105_port_status_mac_unpack(void *buf,
			       struct sja1105_port_status_mac *status)
{
	/* Make pointer arithmetic work on 4 bytes */
	u32 *p = buf;

	sja1105_unpack(p + 0x0, &status->n_runt,       31, 24, 4);
	sja1105_unpack(p + 0x0, &status->n_soferr,     23, 16, 4);
	sja1105_unpack(p + 0x0, &status->n_alignerr,   15,  8, 4);
	sja1105_unpack(p + 0x0, &status->n_miierr,      7,  0, 4);
	sja1105_unpack(p + 0x1, &status->typeerr,      27, 27, 4);
	sja1105_unpack(p + 0x1, &status->sizeerr,      26, 26, 4);
	sja1105_unpack(p + 0x1, &status->tctimeout,    25, 25, 4);
	sja1105_unpack(p + 0x1, &status->priorerr,     24, 24, 4);
	sja1105_unpack(p + 0x1, &status->nomaster,     23, 23, 4);
	sja1105_unpack(p + 0x1, &status->memov,        22, 22, 4);
	sja1105_unpack(p + 0x1, &status->memerr,       21, 21, 4);
	sja1105_unpack(p + 0x1, &status->invtyp,       19, 19, 4);
	sja1105_unpack(p + 0x1, &status->intcyov,      18, 18, 4);
	sja1105_unpack(p + 0x1, &status->domerr,       17, 17, 4);
	sja1105_unpack(p + 0x1, &status->pcfbagdrop,   16, 16, 4);
	sja1105_unpack(p + 0x1, &status->spcprior,     15, 12, 4);
	sja1105_unpack(p + 0x1, &status->ageprior,     11,  8, 4);
	sja1105_unpack(p + 0x1, &status->portdrop,      6,  6, 4);
	sja1105_unpack(p + 0x1, &status->lendrop,       5,  5, 4);
	sja1105_unpack(p + 0x1, &status->bagdrop,       4,  4, 4);
	sja1105_unpack(p + 0x1, &status->policeerr,     3,  3, 4);
	sja1105_unpack(p + 0x1, &status->drpnona664err, 2,  2, 4);
	sja1105_unpack(p + 0x1, &status->spcerr,        1,  1, 4);
	sja1105_unpack(p + 0x1, &status->agedrp,        0,  0, 4);
}