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
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_LINK_CNTL ; 
 int /*<<< orphan*/  DP_LINK_TRAINING_COMPLETE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_link_training_complete(
	struct dcn10_link_encoder *enc10,
	bool complete)
{
	/* This register resides in DP back end block;
	 * transmitter is used for the offset
	 */
	REG_UPDATE(DP_LINK_CNTL, DP_LINK_TRAINING_COMPLETE, complete);

}