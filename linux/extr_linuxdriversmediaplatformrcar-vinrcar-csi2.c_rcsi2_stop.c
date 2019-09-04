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
struct rcar_csi2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHTC_REG ; 
 int /*<<< orphan*/  PHTC_TESTCLR ; 
 int /*<<< orphan*/  PHYCNT_REG ; 
 int /*<<< orphan*/  rcsi2_reset (struct rcar_csi2*) ; 
 int /*<<< orphan*/  rcsi2_write (struct rcar_csi2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcsi2_stop(struct rcar_csi2 *priv)
{
	rcsi2_write(priv, PHYCNT_REG, 0);

	rcsi2_reset(priv);

	rcsi2_write(priv, PHTC_REG, PHTC_TESTCLR);
}