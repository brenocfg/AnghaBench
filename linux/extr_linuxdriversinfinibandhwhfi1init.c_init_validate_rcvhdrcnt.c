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
typedef  int uint ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HDRQ_INCREMENT ; 
 int HFI1_MAX_HDRQ_EGRBUF_CNT ; 
 int HFI1_MIN_HDRQ_EGRBUF_CNT ; 
 int /*<<< orphan*/  hfi1_early_err (struct device*,char*,...) ; 

__attribute__((used)) static int init_validate_rcvhdrcnt(struct device *dev, uint thecnt)
{
	if (thecnt <= HFI1_MIN_HDRQ_EGRBUF_CNT) {
		hfi1_early_err(dev, "Receive header queue count too small\n");
		return -EINVAL;
	}

	if (thecnt > HFI1_MAX_HDRQ_EGRBUF_CNT) {
		hfi1_early_err(dev,
			       "Receive header queue count cannot be greater than %u\n",
			       HFI1_MAX_HDRQ_EGRBUF_CNT);
		return -EINVAL;
	}

	if (thecnt % HDRQ_INCREMENT) {
		hfi1_early_err(dev, "Receive header queue count %d must be divisible by %lu\n",
			       thecnt, HDRQ_INCREMENT);
		return -EINVAL;
	}

	return 0;
}