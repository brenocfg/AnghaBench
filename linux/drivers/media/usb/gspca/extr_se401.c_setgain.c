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
typedef  scalar_t__ u16 ;
struct gspca_dev {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  HV7131_REG_ABCG ; 
 int /*<<< orphan*/  HV7131_REG_AGCG ; 
 int /*<<< orphan*/  HV7131_REG_ARCG ; 
 int /*<<< orphan*/  se401_set_feature (struct gspca_dev*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void setgain(struct gspca_dev *gspca_dev, s32 val)
{
	u16 gain = 63 - val;

	/* red color gain */
	se401_set_feature(gspca_dev, HV7131_REG_ARCG, gain);
	/* green color gain */
	se401_set_feature(gspca_dev, HV7131_REG_AGCG, gain);
	/* blue color gain */
	se401_set_feature(gspca_dev, HV7131_REG_ABCG, gain);
}