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
struct mt7530_priv {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MT7530_MFC ; 
 int /*<<< orphan*/  MT7530_PCR_P (int) ; 
 int /*<<< orphan*/  MT7530_PMCR_P (int) ; 
 int /*<<< orphan*/  MT7530_PSC_P (int) ; 
 int /*<<< orphan*/  MT7530_PVC_P (int) ; 
 int /*<<< orphan*/  PCR_MATRIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCR_CPUP_LINK ; 
 int /*<<< orphan*/  PORT_SPEC_TAG ; 
 int /*<<< orphan*/  SA_DIS ; 
 int /*<<< orphan*/  UNU_FFP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_user_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_set (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_write (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7530_cpu_port_enable(struct mt7530_priv *priv,
		       int port)
{
	/* Enable Mediatek header mode on the cpu port */
	mt7530_write(priv, MT7530_PVC_P(port),
		     PORT_SPEC_TAG);

	/* Setup the MAC by default for the cpu port */
	mt7530_write(priv, MT7530_PMCR_P(port), PMCR_CPUP_LINK);

	/* Disable auto learning on the cpu port */
	mt7530_set(priv, MT7530_PSC_P(port), SA_DIS);

	/* Unknown unicast frame fordwarding to the cpu port */
	mt7530_set(priv, MT7530_MFC, UNU_FFP(BIT(port)));

	/* CPU port gets connected to all user ports of
	 * the switch
	 */
	mt7530_write(priv, MT7530_PCR_P(port),
		     PCR_MATRIX(dsa_user_ports(priv->ds)));

	return 0;
}