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
 int /*<<< orphan*/  S5P_FIMV_RISC2HOST_CMD ; 
 int /*<<< orphan*/  S5P_FIMV_RISC_HOST_INT ; 
 int /*<<< orphan*/  S5P_FIMV_SI_RTN_CHID ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_mfc_clear_int_flags_v5(struct s5p_mfc_dev *dev)
{
	mfc_write(dev, 0, S5P_FIMV_RISC_HOST_INT);
	mfc_write(dev, 0, S5P_FIMV_RISC2HOST_CMD);
	mfc_write(dev, 0xffff, S5P_FIMV_SI_RTN_CHID);
}