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
typedef  unsigned int u32 ;
struct camif_dev {int dummy; } ;

/* Variables and functions */
 unsigned int CIGCTRL_TESTPATTERN_MASK ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CIGCTRL ; 
 unsigned int camif_read (struct camif_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (struct camif_dev*,int /*<<< orphan*/ ,unsigned int) ; 

void camif_hw_set_test_pattern(struct camif_dev *camif, unsigned int pattern)
{
	u32 cfg = camif_read(camif, S3C_CAMIF_REG_CIGCTRL);
	cfg &= ~CIGCTRL_TESTPATTERN_MASK;
	cfg |= (pattern << 27);
	camif_write(camif, S3C_CAMIF_REG_CIGCTRL, cfg);
}