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
typedef  int /*<<< orphan*/  u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  REG_GREEN1_GAIN ; 
 int /*<<< orphan*/  REG_GREEN2_GAIN ; 
 int /*<<< orphan*/  gainify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setggain(struct gspca_dev *gspca_dev, u16 global_gain)
{
	u16 normalized;

	normalized = gainify(global_gain);
	gspca_dbg(gspca_dev, D_STREAM, "gain G1/G2 (0x%04X): 0x%04X (src 0x%04X)\n\n",
		  REG_GREEN1_GAIN,
		  normalized, global_gain);

	reg_w(gspca_dev, normalized, REG_GREEN1_GAIN);
	reg_w(gspca_dev, normalized, REG_GREEN2_GAIN);
}