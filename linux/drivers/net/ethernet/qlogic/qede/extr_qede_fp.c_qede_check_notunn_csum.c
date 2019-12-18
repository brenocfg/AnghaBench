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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;

/* Variables and functions */
 int PARSING_AND_ERR_FLAGS_IPHDRERROR_MASK ; 
 int PARSING_AND_ERR_FLAGS_IPHDRERROR_SHIFT ; 
 int PARSING_AND_ERR_FLAGS_L4CHKSMERROR_MASK ; 
 int PARSING_AND_ERR_FLAGS_L4CHKSMERROR_SHIFT ; 
 int PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED_MASK ; 
 int PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED_SHIFT ; 
 int /*<<< orphan*/  QEDE_CSUM_ERROR ; 
 int /*<<< orphan*/  QEDE_CSUM_UNNECESSARY ; 

__attribute__((used)) static u8 qede_check_notunn_csum(u16 flag)
{
	u16 csum_flag = 0;
	u8 csum = 0;

	if (flag & (PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED_MASK <<
		    PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED_SHIFT)) {
		csum_flag |= PARSING_AND_ERR_FLAGS_L4CHKSMERROR_MASK <<
			     PARSING_AND_ERR_FLAGS_L4CHKSMERROR_SHIFT;
		csum = QEDE_CSUM_UNNECESSARY;
	}

	csum_flag |= PARSING_AND_ERR_FLAGS_IPHDRERROR_MASK <<
		     PARSING_AND_ERR_FLAGS_IPHDRERROR_SHIFT;

	if (csum_flag & flag)
		return QEDE_CSUM_ERROR;

	return csum;
}