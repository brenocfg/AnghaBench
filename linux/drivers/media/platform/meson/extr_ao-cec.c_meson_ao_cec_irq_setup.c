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
struct meson_ao_cec_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CEC_INTR_MASKN_REG ; 
 int CEC_INTR_RX ; 
 int CEC_INTR_TX ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int,scalar_t__) ; 

__attribute__((used)) static inline void meson_ao_cec_irq_setup(struct meson_ao_cec_device *ao_cec,
				      bool enable)
{
	u32 cfg = CEC_INTR_TX | CEC_INTR_RX;

	writel_bits_relaxed(cfg, enable ? cfg : 0,
			    ao_cec->base + CEC_INTR_MASKN_REG);
}