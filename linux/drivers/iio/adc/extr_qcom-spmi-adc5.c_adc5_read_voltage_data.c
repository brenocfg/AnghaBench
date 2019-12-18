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
typedef  int u16 ;
struct adc5_chip {int dummy; } ;
typedef  int /*<<< orphan*/  rslt_lsb ;

/* Variables and functions */
 int /*<<< orphan*/  ADC5_USR_DATA0 ; 
 int /*<<< orphan*/  ADC5_USR_DATA1 ; 
 int ADC5_USR_DATA_CHECK ; 
 int EINVAL ; 
 int adc5_read (struct adc5_chip*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int adc5_read_voltage_data(struct adc5_chip *adc, u16 *data)
{
	int ret;
	u8 rslt_lsb, rslt_msb;

	ret = adc5_read(adc, ADC5_USR_DATA0, &rslt_lsb, sizeof(rslt_lsb));
	if (ret)
		return ret;

	ret = adc5_read(adc, ADC5_USR_DATA1, &rslt_msb, sizeof(rslt_lsb));
	if (ret)
		return ret;

	*data = (rslt_msb << 8) | rslt_lsb;

	if (*data == ADC5_USR_DATA_CHECK) {
		pr_err("Invalid data:0x%x\n", *data);
		return -EINVAL;
	}

	pr_debug("voltage raw code:0x%x\n", *data);

	return 0;
}