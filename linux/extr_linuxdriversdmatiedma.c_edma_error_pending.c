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
struct edma_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_CCERR ; 
 int /*<<< orphan*/  EDMA_EMR ; 
 int /*<<< orphan*/  EDMA_QEMR ; 
 scalar_t__ edma_read (struct edma_cc*,int /*<<< orphan*/ ) ; 
 scalar_t__ edma_read_array (struct edma_cc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool edma_error_pending(struct edma_cc *ecc)
{
	if (edma_read_array(ecc, EDMA_EMR, 0) ||
	    edma_read_array(ecc, EDMA_EMR, 1) ||
	    edma_read(ecc, EDMA_QEMR) || edma_read(ecc, EDMA_CCERR))
		return true;

	return false;
}