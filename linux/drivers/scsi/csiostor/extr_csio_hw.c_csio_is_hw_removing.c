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
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csio_hws_removing ; 
 int csio_match_state (struct csio_hw*,int /*<<< orphan*/ ) ; 

int csio_is_hw_removing(struct csio_hw *hw)
{
	return csio_match_state(hw, csio_hws_removing);
}