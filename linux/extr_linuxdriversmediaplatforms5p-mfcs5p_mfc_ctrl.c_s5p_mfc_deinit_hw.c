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
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_dev_context_buffer ; 
 int /*<<< orphan*/  s5p_mfc_clock_off () ; 
 int /*<<< orphan*/  s5p_mfc_clock_on () ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  s5p_mfc_reset (struct s5p_mfc_dev*) ; 

void s5p_mfc_deinit_hw(struct s5p_mfc_dev *dev)
{
	s5p_mfc_clock_on();

	s5p_mfc_reset(dev);
	s5p_mfc_hw_call(dev->mfc_ops, release_dev_context_buffer, dev);

	s5p_mfc_clock_off();
}