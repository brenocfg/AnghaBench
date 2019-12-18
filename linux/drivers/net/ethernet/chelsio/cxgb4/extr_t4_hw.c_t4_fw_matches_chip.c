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
struct fw_hdr {scalar_t__ chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_HDR_CHIP_T4 ; 
 scalar_t__ FW_HDR_CHIP_T5 ; 
 scalar_t__ FW_HDR_CHIP_T6 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool t4_fw_matches_chip(const struct adapter *adap,
			       const struct fw_hdr *hdr)
{
	/* The expression below will return FALSE for any unsupported adapter
	 * which will keep us "honest" in the future ...
	 */
	if ((is_t4(adap->params.chip) && hdr->chip == FW_HDR_CHIP_T4) ||
	    (is_t5(adap->params.chip) && hdr->chip == FW_HDR_CHIP_T5) ||
	    (is_t6(adap->params.chip) && hdr->chip == FW_HDR_CHIP_T6))
		return true;

	dev_err(adap->pdev_dev,
		"FW image (%d) is not suitable for this adapter (%d)\n",
		hdr->chip, CHELSIO_CHIP_VERSION(adap->params.chip));
	return false;
}