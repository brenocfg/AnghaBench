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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ rounding ;
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_QOS ; 
 int /*<<< orphan*/  PRINTD (int,char*,unsigned int,char*,unsigned int) ; 
 int make_rate (int /*<<< orphan*/  const*,unsigned int,scalar_t__,int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ round_down ; 
 scalar_t__ round_nearest ; 
 scalar_t__ round_up ; 

__attribute__((used)) static int make_rate_with_tolerance (const hrz_dev * dev, u32 c, rounding r, unsigned int tol,
				     u16 * bit_pattern, unsigned int * actual) {
  unsigned int my_actual;
  
  PRINTD (DBG_QOS|DBG_FLOW, "make_rate_with_tolerance c=%u, %s, tol=%u",
	  c, (r == round_up) ? "up" : (r == round_down) ? "down" : "nearest", tol);
  
  if (!actual)
    // actual rate is not returned
    actual = &my_actual;
  
  if (make_rate (dev, c, round_nearest, bit_pattern, actual))
    // should never happen as round_nearest always succeeds
    return -1;
  
  if (c - tol <= *actual && *actual <= c + tol)
    // within tolerance
    return 0;
  else
    // intolerant, try rounding instead
    return make_rate (dev, c, r, bit_pattern, actual);
}