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
typedef  scalar_t__ u16 ;
struct altera_tse_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGMII_PCS_SCRATCH ; 
 scalar_t__ sgmii_pcs_read (struct altera_tse_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgmii_pcs_write (struct altera_tse_private*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sgmii_pcs_scratch_test(struct altera_tse_private *priv, u16 value)
{
	sgmii_pcs_write(priv, SGMII_PCS_SCRATCH, value);
	return (sgmii_pcs_read(priv, SGMII_PCS_SCRATCH) == value);
}