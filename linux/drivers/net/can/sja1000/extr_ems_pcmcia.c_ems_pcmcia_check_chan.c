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
struct sja1000_priv {int dummy; } ;

/* Variables and functions */
 int CDR_PELICAN ; 
 int /*<<< orphan*/  SJA1000_CDR ; 
 int /*<<< orphan*/  SJA1000_MOD ; 
 int ems_pcmcia_read_reg (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ems_pcmcia_write_reg (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int ems_pcmcia_check_chan(struct sja1000_priv *priv)
{
	/* Make sure SJA1000 is in reset mode */
	ems_pcmcia_write_reg(priv, SJA1000_MOD, 1);
	ems_pcmcia_write_reg(priv, SJA1000_CDR, CDR_PELICAN);

	/* read reset-values */
	if (ems_pcmcia_read_reg(priv, SJA1000_CDR) == CDR_PELICAN)
		return 1;

	return 0;
}