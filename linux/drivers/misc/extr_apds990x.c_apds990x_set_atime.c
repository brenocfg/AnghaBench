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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct apds990x_chip {int atime; int a_max_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS990X_ATIME ; 
 int APDS990X_TIME_TO_ADC ; 
 int TIMESTEP ; 
 int TIME_STEP_SCALER ; 
 int apds990x_write_byte (struct apds990x_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int apds990x_set_atime(struct apds990x_chip *chip, u32 time_ms)
{
	u8 reg_value;

	chip->atime = time_ms;
	/* Formula is specified in the data sheet */
	reg_value = 256 - ((time_ms * TIME_STEP_SCALER) / TIMESTEP);
	/* Calculate max ADC value for given integration time */
	chip->a_max_result = (u16)(256 - reg_value) * APDS990X_TIME_TO_ADC;
	return apds990x_write_byte(chip, APDS990X_ATIME, reg_value);
}