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
struct mga_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_DATA ; 
 int /*<<< orphan*/  DAC_INDEX ; 
 int /*<<< orphan*/  MGA1064_GEN_IO_DATA ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mga_i2c_read_gpio(struct mga_device *mdev)
{
	WREG8(DAC_INDEX, MGA1064_GEN_IO_DATA);
	return RREG8(DAC_DATA);
}