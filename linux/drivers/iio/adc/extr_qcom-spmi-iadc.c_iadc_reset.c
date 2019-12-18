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
typedef  int /*<<< orphan*/  u8 ;
struct iadc_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IADC_FOLLOW_WARM_RB ; 
 int /*<<< orphan*/  IADC_PERH_RESET_CTL3 ; 
 int /*<<< orphan*/  IADC_SEC_ACCESS ; 
 int /*<<< orphan*/  IADC_SEC_ACCESS_DATA ; 
 int iadc_read (struct iadc_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iadc_write (struct iadc_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iadc_reset(struct iadc_chip *iadc)
{
	u8 data;
	int ret;

	ret = iadc_write(iadc, IADC_SEC_ACCESS, IADC_SEC_ACCESS_DATA);
	if (ret < 0)
		return ret;

	ret = iadc_read(iadc, IADC_PERH_RESET_CTL3, &data);
	if (ret < 0)
		return ret;

	ret = iadc_write(iadc, IADC_SEC_ACCESS, IADC_SEC_ACCESS_DATA);
	if (ret < 0)
		return ret;

	data |= IADC_FOLLOW_WARM_RB;

	return iadc_write(iadc, IADC_PERH_RESET_CTL3, data);
}