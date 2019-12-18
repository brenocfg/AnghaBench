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
struct imx7_csi {scalar_t__ regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void imx7_csi_reg_write(struct imx7_csi *csi, unsigned int value,
			       unsigned int offset)
{
	writel(value, csi->regbase + offset);
}