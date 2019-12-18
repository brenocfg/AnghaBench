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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  TW_Device_Extension ;

/* Variables and functions */
 scalar_t__ TW_STATUS_ERRORS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_STATUS_REG_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 scalar_t__ tw_check_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_decode_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw_check_errors(TW_Device_Extension *tw_dev) 
{
	u32 status_reg_value;
  
	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

	if (TW_STATUS_ERRORS(status_reg_value) || tw_check_bits(status_reg_value)) {
		tw_decode_bits(tw_dev, status_reg_value, 0);
		return 1;
	}

	return 0;
}