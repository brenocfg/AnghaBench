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
struct s5p_mfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5P_FIMV_SI_DISPLAY_STATUS ; 
 int mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_get_dspl_status_v5(struct s5p_mfc_dev *dev)
{
	return mfc_read(dev, S5P_FIMV_SI_DISPLAY_STATUS);
}