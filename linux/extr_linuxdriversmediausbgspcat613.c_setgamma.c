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
struct gspca_dev {int dummy; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/ * gamma_table ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  reg_w_ixbuf (struct gspca_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setgamma(struct gspca_dev *gspca_dev, s32 val)
{
	gspca_dbg(gspca_dev, D_CONF, "Gamma: %d\n", val);
	reg_w_ixbuf(gspca_dev, 0x90,
		gamma_table[val], sizeof gamma_table[0]);
}