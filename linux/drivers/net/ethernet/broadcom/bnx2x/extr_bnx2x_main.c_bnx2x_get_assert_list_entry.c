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
struct bnx2x {int dummy; } ;
typedef  enum storms { ____Placeholder_storms } storms ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
#define  CSTORM 132 
 int CSTORM_ASSERT_LIST_OFFSET (int) ; 
 int EINVAL ; 
#define  MAX_STORMS 131 
#define  TSTORM 130 
 int TSTORM_ASSERT_LIST_OFFSET (int) ; 
#define  USTORM 129 
 int USTORM_ASSERT_LIST_OFFSET (int) ; 
#define  XSTORM 128 
 int XSTORM_ASSERT_LIST_OFFSET (int) ; 

__attribute__((used)) static inline int bnx2x_get_assert_list_entry(struct bnx2x *bp,
					      enum storms storm,
					      int entry)
{
	switch (storm) {
	case XSTORM:
		return XSTORM_ASSERT_LIST_OFFSET(entry);
	case TSTORM:
		return TSTORM_ASSERT_LIST_OFFSET(entry);
	case CSTORM:
		return CSTORM_ASSERT_LIST_OFFSET(entry);
	case USTORM:
		return USTORM_ASSERT_LIST_OFFSET(entry);
	case MAX_STORMS:
	default:
		BNX2X_ERR("unknown storm\n");
	}
	return -EINVAL;
}