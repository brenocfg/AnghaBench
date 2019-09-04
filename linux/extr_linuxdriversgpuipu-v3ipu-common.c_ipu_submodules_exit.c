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
struct ipu_soc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_cpmem_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_csi_exit (struct ipu_soc*,int) ; 
 int /*<<< orphan*/  ipu_dc_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_di_exit (struct ipu_soc*,int) ; 
 int /*<<< orphan*/  ipu_dmfc_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_dp_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_ic_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_image_convert_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_smfc_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_vdi_exit (struct ipu_soc*) ; 

__attribute__((used)) static void ipu_submodules_exit(struct ipu_soc *ipu)
{
	ipu_smfc_exit(ipu);
	ipu_dp_exit(ipu);
	ipu_dmfc_exit(ipu);
	ipu_dc_exit(ipu);
	ipu_di_exit(ipu, 1);
	ipu_di_exit(ipu, 0);
	ipu_image_convert_exit(ipu);
	ipu_vdi_exit(ipu);
	ipu_ic_exit(ipu);
	ipu_csi_exit(ipu, 1);
	ipu_csi_exit(ipu, 0);
	ipu_cpmem_exit(ipu);
}