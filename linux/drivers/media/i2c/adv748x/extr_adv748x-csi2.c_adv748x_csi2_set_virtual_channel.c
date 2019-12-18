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
struct adv748x_csi2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CSI_VC_REF ; 
 unsigned int ADV748X_CSI_VC_REF_SHIFT ; 
 int tx_write (struct adv748x_csi2*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adv748x_csi2_set_virtual_channel(struct adv748x_csi2 *tx,
					    unsigned int vc)
{
	return tx_write(tx, ADV748X_CSI_VC_REF, vc << ADV748X_CSI_VC_REF_SHIFT);
}