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
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_ops; int /*<<< orphan*/  warn_start; } ;

/* Variables and functions */
 scalar_t__ IS_MFCV6_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  S5P_FIMV_ERR_WARNINGS_START ; 
 int /*<<< orphan*/  S5P_FIMV_ERR_WARNINGS_START_V6 ; 
 int /*<<< orphan*/  s5p_mfc_init_hw_ops_v5 () ; 
 int /*<<< orphan*/  s5p_mfc_init_hw_ops_v6 () ; 
 int /*<<< orphan*/  s5p_mfc_ops ; 

void s5p_mfc_init_hw_ops(struct s5p_mfc_dev *dev)
{
	if (IS_MFCV6_PLUS(dev)) {
		s5p_mfc_ops = s5p_mfc_init_hw_ops_v6();
		dev->warn_start = S5P_FIMV_ERR_WARNINGS_START_V6;
	} else {
		s5p_mfc_ops = s5p_mfc_init_hw_ops_v5();
		dev->warn_start = S5P_FIMV_ERR_WARNINGS_START;
	}
	dev->mfc_ops = s5p_mfc_ops;
}