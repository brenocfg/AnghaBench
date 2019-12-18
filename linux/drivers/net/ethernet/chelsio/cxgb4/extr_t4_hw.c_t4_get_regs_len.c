#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ params; } ;

/* Variables and functions */
 unsigned int CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
#define  CHELSIO_T4 130 
#define  CHELSIO_T5 129 
#define  CHELSIO_T6 128 
 unsigned int T4_REGMAP_SIZE ; 
 unsigned int T5_REGMAP_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 

unsigned int t4_get_regs_len(struct adapter *adapter)
{
	unsigned int chip_version = CHELSIO_CHIP_VERSION(adapter->params.chip);

	switch (chip_version) {
	case CHELSIO_T4:
		return T4_REGMAP_SIZE;

	case CHELSIO_T5:
	case CHELSIO_T6:
		return T5_REGMAP_SIZE;
	}

	dev_err(adapter->pdev_dev,
		"Unsupported chip version %d\n", chip_version);
	return 0;
}