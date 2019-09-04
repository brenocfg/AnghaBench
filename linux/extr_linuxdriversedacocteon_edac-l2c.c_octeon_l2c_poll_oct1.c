#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sec_err; int ded_err; } ;
union cvmx_l2t_err {void* u64; TYPE_1__ s; } ;
struct TYPE_4__ {int sec_err; int ded_err; } ;
union cvmx_l2d_err {void* u64; TYPE_2__ s; } ;
struct edac_device_ctl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2D_ERR ; 
 int /*<<< orphan*/  CVMX_L2T_ERR ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void octeon_l2c_poll_oct1(struct edac_device_ctl_info *l2c)
{
	union cvmx_l2t_err l2t_err, l2t_err_reset;
	union cvmx_l2d_err l2d_err, l2d_err_reset;

	l2t_err_reset.u64 = 0;
	l2t_err.u64 = cvmx_read_csr(CVMX_L2T_ERR);
	if (l2t_err.s.sec_err) {
		edac_device_handle_ce(l2c, 0, 0,
				      "Tag Single bit error (corrected)");
		l2t_err_reset.s.sec_err = 1;
	}
	if (l2t_err.s.ded_err) {
		edac_device_handle_ue(l2c, 0, 0,
				      "Tag Double bit error (detected)");
		l2t_err_reset.s.ded_err = 1;
	}
	if (l2t_err_reset.u64)
		cvmx_write_csr(CVMX_L2T_ERR, l2t_err_reset.u64);

	l2d_err_reset.u64 = 0;
	l2d_err.u64 = cvmx_read_csr(CVMX_L2D_ERR);
	if (l2d_err.s.sec_err) {
		edac_device_handle_ce(l2c, 0, 1,
				      "Data Single bit error (corrected)");
		l2d_err_reset.s.sec_err = 1;
	}
	if (l2d_err.s.ded_err) {
		edac_device_handle_ue(l2c, 0, 1,
				      "Data Double bit error (detected)");
		l2d_err_reset.s.ded_err = 1;
	}
	if (l2d_err_reset.u64)
		cvmx_write_csr(CVMX_L2D_ERR, l2d_err_reset.u64);

}