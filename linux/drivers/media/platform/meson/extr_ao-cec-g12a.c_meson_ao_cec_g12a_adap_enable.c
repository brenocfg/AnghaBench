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
struct meson_ao_cec_g12a_device {int /*<<< orphan*/  regmap_cec; TYPE_1__* data; int /*<<< orphan*/  regmap; } ;
struct cec_adapter {struct meson_ao_cec_g12a_device* priv; } ;
struct TYPE_2__ {scalar_t__ ctrl2_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  CECB_CTRL2 ; 
 int CECB_CTRL2_RISE_DEL_MAX ; 
 int CECB_GEN_CNTL_CLK_CTRL_MASK ; 
 int CECB_GEN_CNTL_CLK_ENABLE ; 
 int CECB_GEN_CNTL_FILTER_DEL ; 
 int CECB_GEN_CNTL_FILTER_TICK_1US ; 
 int CECB_GEN_CNTL_FILTER_TICK_SEL ; 
 int /*<<< orphan*/  CECB_GEN_CNTL_REG ; 
 int CECB_GEN_CNTL_RESET ; 
 int CECB_GEN_CNTL_SYS_CLK_EN ; 
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  meson_ao_cec_g12a_irq_setup (struct meson_ao_cec_g12a_device*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meson_ao_cec_g12a_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct meson_ao_cec_g12a_device *ao_cec = adap->priv;

	meson_ao_cec_g12a_irq_setup(ao_cec, false);

	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_RESET, CECB_GEN_CNTL_RESET);

	if (!enable)
		return 0;

	/* Setup Filter */
	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_FILTER_TICK_SEL |
			   CECB_GEN_CNTL_FILTER_DEL,
			   FIELD_PREP(CECB_GEN_CNTL_FILTER_TICK_SEL,
				      CECB_GEN_CNTL_FILTER_TICK_1US) |
			   FIELD_PREP(CECB_GEN_CNTL_FILTER_DEL, 7));

	/* Enable System Clock */
	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_SYS_CLK_EN,
			   CECB_GEN_CNTL_SYS_CLK_EN);

	/* Enable gated clock (Normal mode). */
	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_CLK_CTRL_MASK,
			    FIELD_PREP(CECB_GEN_CNTL_CLK_CTRL_MASK,
				       CECB_GEN_CNTL_CLK_ENABLE));

	/* Release Reset */
	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_RESET, 0);

	if (ao_cec->data->ctrl2_setup)
		regmap_write(ao_cec->regmap_cec, CECB_CTRL2,
			     FIELD_PREP(CECB_CTRL2_RISE_DEL_MAX, 2));

	meson_ao_cec_g12a_irq_setup(ao_cec, true);

	return 0;
}