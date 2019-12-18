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
struct ni_gpct_device {int variant; } ;
struct ni_gpct {unsigned int counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GI_660X_HW_ARM_SEL_MASK ; 
 unsigned int GI_ARM ; 
 unsigned int GI_ARM_COPY ; 
 unsigned int GI_DISARM ; 
 unsigned int GI_HW_ARM_ENA ; 
 unsigned int GI_HW_ARM_SEL (unsigned int) ; 
 unsigned int GI_M_HW_ARM_SEL_MASK ; 
 int /*<<< orphan*/  NITIO_CMD_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_CNT_MODE_REG (unsigned int) ; 
#define  NI_GPCT_ARM_IMMEDIATE 132 
#define  NI_GPCT_ARM_PAIRED_IMMEDIATE 131 
 unsigned int NI_GPCT_ARM_UNKNOWN ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_bits_transient (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int ni_tio_arm(struct ni_gpct *counter, bool arm, unsigned int start_trigger)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int transient_bits = 0;

	if (arm) {
		unsigned int mask = 0;
		unsigned int bits = 0;

		/* only m series and 660x have counting mode registers */
		switch (counter_dev->variant) {
		case ni_gpct_variant_e_series:
		default:
			break;
		case ni_gpct_variant_m_series:
			mask = GI_M_HW_ARM_SEL_MASK;
			break;
		case ni_gpct_variant_660x:
			mask = GI_660X_HW_ARM_SEL_MASK;
			break;
		}

		switch (start_trigger) {
		case NI_GPCT_ARM_IMMEDIATE:
			transient_bits |= GI_ARM;
			break;
		case NI_GPCT_ARM_PAIRED_IMMEDIATE:
			transient_bits |= GI_ARM | GI_ARM_COPY;
			break;
		default:
			/*
			 * for m series and 660x, pass-through the least
			 * significant bits so we can figure out what select
			 * later
			 */
			if (mask && (start_trigger & NI_GPCT_ARM_UNKNOWN)) {
				bits |= GI_HW_ARM_ENA |
					(GI_HW_ARM_SEL(start_trigger) & mask);
			} else {
				return -EINVAL;
			}
			break;
		}

		if (mask)
			ni_tio_set_bits(counter, NITIO_CNT_MODE_REG(cidx),
					GI_HW_ARM_ENA | mask, bits);
	} else {
		transient_bits |= GI_DISARM;
	}
	ni_tio_set_bits_transient(counter, NITIO_CMD_REG(cidx),
				  0, 0, transient_bits);
	return 0;
}