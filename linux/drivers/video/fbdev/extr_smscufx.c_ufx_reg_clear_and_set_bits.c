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
struct ufx_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_warn_return (int,char*,int /*<<< orphan*/ ) ; 
 int ufx_reg_read (struct ufx_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ufx_reg_write (struct ufx_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufx_reg_clear_and_set_bits(struct ufx_data *dev, u32 index,
	u32 bits_to_clear, u32 bits_to_set)
{
	u32 data;
	int status = ufx_reg_read(dev, index, &data);
	check_warn_return(status, "ufx_reg_clear_and_set_bits error reading "
		"0x%x", index);

	data &= (~bits_to_clear);
	data |= bits_to_set;

	status = ufx_reg_write(dev, index, data);
	check_warn_return(status, "ufx_reg_clear_and_set_bits error writing "
		"0x%x", index);

	return 0;
}