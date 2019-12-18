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
typedef  int u32 ;
struct meson_ao_cec_g12a_device {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int CECB_INTR_ARB_LOSS ; 
 int CECB_INTR_DONE ; 
 int CECB_INTR_EOM ; 
 int CECB_INTR_FOLLOWER_ERR ; 
 int CECB_INTR_INITIATOR_ERR ; 
 int /*<<< orphan*/  CECB_INTR_MASKN_REG ; 
 int CECB_INTR_NACK ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
meson_ao_cec_g12a_irq_setup(struct meson_ao_cec_g12a_device *ao_cec,
			    bool enable)
{
	u32 cfg = CECB_INTR_DONE | CECB_INTR_EOM | CECB_INTR_NACK |
		  CECB_INTR_ARB_LOSS | CECB_INTR_INITIATOR_ERR |
		  CECB_INTR_FOLLOWER_ERR;

	regmap_write(ao_cec->regmap, CECB_INTR_MASKN_REG,
		     enable ? cfg : 0);
}