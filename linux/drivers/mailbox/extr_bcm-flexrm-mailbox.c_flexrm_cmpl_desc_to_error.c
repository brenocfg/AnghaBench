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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CMPL_DME_STATUS_MASK ; 
 int /*<<< orphan*/  CMPL_DME_STATUS_SHIFT ; 
 int /*<<< orphan*/  CMPL_RM_STATUS_MASK ; 
 int /*<<< orphan*/  CMPL_RM_STATUS_SHIFT ; 
 int DESC_DEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DME_STATUS_ERROR_MASK ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int RM_STATUS_CODE_AE_TIMEOUT ; 
 int RM_STATUS_CODE_MASK ; 

__attribute__((used)) static int flexrm_cmpl_desc_to_error(u64 cmpl_desc)
{
	u32 status;

	status = DESC_DEC(cmpl_desc, CMPL_DME_STATUS_SHIFT,
			  CMPL_DME_STATUS_MASK);
	if (status & DME_STATUS_ERROR_MASK)
		return -EIO;

	status = DESC_DEC(cmpl_desc, CMPL_RM_STATUS_SHIFT,
			  CMPL_RM_STATUS_MASK);
	status &= RM_STATUS_CODE_MASK;
	if (status == RM_STATUS_CODE_AE_TIMEOUT)
		return -ETIMEDOUT;

	return 0;
}