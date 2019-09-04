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
typedef  int /*<<< orphan*/  u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int reg_r (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reg_w_mask(struct gspca_dev *gspca_dev, u16 index, u8 val, u8 mask)
{
	val = (reg_r(gspca_dev, index) & ~mask) | (val & mask);
	reg_w(gspca_dev, index, val);
}