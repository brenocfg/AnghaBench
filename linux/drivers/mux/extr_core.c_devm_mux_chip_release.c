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
struct mux_chip {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mux_chip_free (struct mux_chip*) ; 

__attribute__((used)) static void devm_mux_chip_release(struct device *dev, void *res)
{
	struct mux_chip *mux_chip = *(struct mux_chip **)res;

	mux_chip_free(mux_chip);
}