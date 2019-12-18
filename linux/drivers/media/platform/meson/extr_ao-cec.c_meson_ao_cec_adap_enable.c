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
struct meson_ao_cec_device {scalar_t__ base; } ;
struct cec_adapter {struct meson_ao_cec_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_GEN_CNTL_CLK_CTRL_MASK ; 
 int /*<<< orphan*/  CEC_GEN_CNTL_CLK_ENABLE ; 
 scalar_t__ CEC_GEN_CNTL_REG ; 
 int /*<<< orphan*/  CEC_GEN_CNTL_RESET ; 
 int /*<<< orphan*/  CEC_SIGNAL_FREE_TIME_NEW_INITIATOR ; 
 int /*<<< orphan*/  CEC_SIGNAL_FREE_TIME_NEXT_XFER ; 
 int /*<<< orphan*/  CEC_SIGNAL_FREE_TIME_RETRY ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int meson_ao_cec_arbit_bit_time_set (struct meson_ao_cec_device*,int /*<<< orphan*/ ,int) ; 
 int meson_ao_cec_clear (struct meson_ao_cec_device*) ; 
 int /*<<< orphan*/  meson_ao_cec_irq_setup (struct meson_ao_cec_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_ao_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct meson_ao_cec_device *ao_cec = adap->priv;
	int ret;

	meson_ao_cec_irq_setup(ao_cec, false);

	writel_bits_relaxed(CEC_GEN_CNTL_RESET, CEC_GEN_CNTL_RESET,
			    ao_cec->base + CEC_GEN_CNTL_REG);

	if (!enable)
		return 0;

	/* Enable gated clock (Normal mode). */
	writel_bits_relaxed(CEC_GEN_CNTL_CLK_CTRL_MASK,
			    FIELD_PREP(CEC_GEN_CNTL_CLK_CTRL_MASK,
				       CEC_GEN_CNTL_CLK_ENABLE),
			    ao_cec->base + CEC_GEN_CNTL_REG);

	udelay(100);

	/* Release Reset */
	writel_bits_relaxed(CEC_GEN_CNTL_RESET, 0,
			    ao_cec->base + CEC_GEN_CNTL_REG);

	/* Clear buffers */
	ret = meson_ao_cec_clear(ao_cec);
	if (ret)
		return ret;

	/* CEC arbitration 3/5/7 bit time set. */
	ret = meson_ao_cec_arbit_bit_time_set(ao_cec,
					CEC_SIGNAL_FREE_TIME_RETRY,
					0x118);
	if (ret)
		return ret;
	ret = meson_ao_cec_arbit_bit_time_set(ao_cec,
					CEC_SIGNAL_FREE_TIME_NEW_INITIATOR,
					0x000);
	if (ret)
		return ret;
	ret = meson_ao_cec_arbit_bit_time_set(ao_cec,
					CEC_SIGNAL_FREE_TIME_NEXT_XFER,
					0x2aa);
	if (ret)
		return ret;

	meson_ao_cec_irq_setup(ao_cec, true);

	return 0;
}