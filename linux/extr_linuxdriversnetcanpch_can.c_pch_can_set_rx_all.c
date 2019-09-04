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
struct pch_can_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_RX_IFREG ; 
 int PCH_RX_OBJ_END ; 
 int PCH_RX_OBJ_START ; 
 int /*<<< orphan*/  pch_can_set_rxtx (struct pch_can_priv*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_can_set_rx_all(struct pch_can_priv *priv, int set)
{
	int i;

	/* Traversing to obtain the object configured as receivers. */
	for (i = PCH_RX_OBJ_START; i <= PCH_RX_OBJ_END; i++)
		pch_can_set_rxtx(priv, i, set, PCH_RX_IFREG);
}