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
typedef  union ieee754dp {int dummy; } ieee754dp ;
struct TYPE_2__ {int nan2008; } ;

/* Variables and functions */
 int DPMANT (union ieee754dp) ; 
 scalar_t__ DP_FBITS ; 
 int DP_MBIT (scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ ieee754_csr ; 
 int /*<<< orphan*/  ieee754dp_isnan (union ieee754dp) ; 

__attribute__((used)) static inline int ieee754dp_issnan(union ieee754dp x)
{
	int qbit;

	assert(ieee754dp_isnan(x));
	qbit = (DPMANT(x) & DP_MBIT(DP_FBITS - 1)) == DP_MBIT(DP_FBITS - 1);
	return ieee754_csr.nan2008 ^ qbit;
}