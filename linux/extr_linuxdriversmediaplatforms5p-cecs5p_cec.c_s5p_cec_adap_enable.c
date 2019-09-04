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
struct s5p_cec_dev {int /*<<< orphan*/  dev; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 struct s5p_cec_dev* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_cec_enable_rx (struct s5p_cec_dev*) ; 
 int /*<<< orphan*/  s5p_cec_mask_rx_interrupts (struct s5p_cec_dev*) ; 
 int /*<<< orphan*/  s5p_cec_mask_tx_interrupts (struct s5p_cec_dev*) ; 
 int /*<<< orphan*/  s5p_cec_reset (struct s5p_cec_dev*) ; 
 int /*<<< orphan*/  s5p_cec_set_divider (struct s5p_cec_dev*) ; 
 int /*<<< orphan*/  s5p_cec_threshold (struct s5p_cec_dev*) ; 
 int /*<<< orphan*/  s5p_cec_unmask_rx_interrupts (struct s5p_cec_dev*) ; 
 int /*<<< orphan*/  s5p_cec_unmask_tx_interrupts (struct s5p_cec_dev*) ; 

__attribute__((used)) static int s5p_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct s5p_cec_dev *cec = cec_get_drvdata(adap);

	if (enable) {
		pm_runtime_get_sync(cec->dev);

		s5p_cec_reset(cec);

		s5p_cec_set_divider(cec);
		s5p_cec_threshold(cec);

		s5p_cec_unmask_tx_interrupts(cec);
		s5p_cec_unmask_rx_interrupts(cec);
		s5p_cec_enable_rx(cec);
	} else {
		s5p_cec_mask_tx_interrupts(cec);
		s5p_cec_mask_rx_interrupts(cec);
		pm_runtime_disable(cec->dev);
	}

	return 0;
}