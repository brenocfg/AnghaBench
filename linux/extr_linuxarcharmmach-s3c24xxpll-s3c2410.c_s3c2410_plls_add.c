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
struct subsys_interface {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_vals_12MHz ; 
 int s3c_plltab_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2410_plls_add(struct device *dev, struct subsys_interface *sif)
{
	return s3c_plltab_register(pll_vals_12MHz, ARRAY_SIZE(pll_vals_12MHz));
}