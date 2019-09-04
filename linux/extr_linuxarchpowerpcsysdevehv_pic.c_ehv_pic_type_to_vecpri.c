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

/* Variables and functions */
 unsigned int EHV_PIC_INFO (int /*<<< orphan*/ ) ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  VECPRI_POLARITY_NEGATIVE ; 
 int /*<<< orphan*/  VECPRI_POLARITY_POSITIVE ; 
 int /*<<< orphan*/  VECPRI_SENSE_EDGE ; 
 int /*<<< orphan*/  VECPRI_SENSE_LEVEL ; 

__attribute__((used)) static unsigned int ehv_pic_type_to_vecpri(unsigned int type)
{
	/* Now convert sense value */

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_RISING:
		return EHV_PIC_INFO(VECPRI_SENSE_EDGE) |
		       EHV_PIC_INFO(VECPRI_POLARITY_POSITIVE);

	case IRQ_TYPE_EDGE_FALLING:
	case IRQ_TYPE_EDGE_BOTH:
		return EHV_PIC_INFO(VECPRI_SENSE_EDGE) |
		       EHV_PIC_INFO(VECPRI_POLARITY_NEGATIVE);

	case IRQ_TYPE_LEVEL_HIGH:
		return EHV_PIC_INFO(VECPRI_SENSE_LEVEL) |
		       EHV_PIC_INFO(VECPRI_POLARITY_POSITIVE);

	case IRQ_TYPE_LEVEL_LOW:
	default:
		return EHV_PIC_INFO(VECPRI_SENSE_LEVEL) |
		       EHV_PIC_INFO(VECPRI_POLARITY_NEGATIVE);
	}
}