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
 int /*<<< orphan*/  SRST_REG ; 
 int /*<<< orphan*/  SRST_SRST ; 
 int /*<<< orphan*/  rcsi2_write (struct rcar_csi2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rcsi2_reset(struct rcar_csi2 *priv)
{
	rcsi2_write(priv, SRST_REG, SRST_SRST);
	usleep_range(100, 150);
	rcsi2_write(priv, SRST_REG, 0);
}