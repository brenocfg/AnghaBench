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
typedef  int /*<<< orphan*/  u16 ;
struct sifive_serial_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ssp_early_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ssp_writel(u32 v, u16 offs, struct sifive_serial_port *ssp)
{
	__ssp_early_writel(v, offs, &ssp->port);
}