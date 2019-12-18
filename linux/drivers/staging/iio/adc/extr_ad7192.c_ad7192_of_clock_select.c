#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_6__ {TYPE_2__* spi; } ;
struct ad7192_state {int /*<<< orphan*/  mclk; TYPE_3__ sd; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 unsigned int AD7192_CLK_EXT_MCLK1_2 ; 
 unsigned int AD7192_CLK_EXT_MCLK2 ; 
 unsigned int AD7192_CLK_INT ; 
 unsigned int AD7192_CLK_INT_CO ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int ad7192_of_clock_select(struct ad7192_state *st)
{
	struct device_node *np = st->sd.spi->dev.of_node;
	unsigned int clock_sel;

	clock_sel = AD7192_CLK_INT;

	/* use internal clock */
	if (PTR_ERR(st->mclk) == -ENOENT) {
		if (of_property_read_bool(np, "adi,int-clock-output-enable"))
			clock_sel = AD7192_CLK_INT_CO;
	} else {
		if (of_property_read_bool(np, "adi,clock-xtal"))
			clock_sel = AD7192_CLK_EXT_MCLK1_2;
		else
			clock_sel = AD7192_CLK_EXT_MCLK2;
	}

	return clock_sel;
}