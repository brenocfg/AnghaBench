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
struct format_data_t {int dummy; } ;
struct eckd_count {int dummy; } ;
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 struct dasd_ccw_req* dasd_eckd_build_check (struct dasd_device*,struct format_data_t*,int,struct eckd_count*,int) ; 
 struct dasd_ccw_req* dasd_eckd_build_check_tcw (struct dasd_device*,struct format_data_t*,int,struct eckd_count*,int) ; 
 struct dasd_ccw_req* dasd_eckd_build_format (struct dasd_device*,int /*<<< orphan*/ *,struct format_data_t*,int) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_eckd_format_build_ccw_req(struct dasd_device *base,
			       struct format_data_t *fdata, int enable_pav,
			       int tpm, struct eckd_count *fmt_buffer, int rpt)
{
	struct dasd_ccw_req *ccw_req;

	if (!fmt_buffer) {
		ccw_req = dasd_eckd_build_format(base, NULL, fdata, enable_pav);
	} else {
		if (tpm)
			ccw_req = dasd_eckd_build_check_tcw(base, fdata,
							    enable_pav,
							    fmt_buffer, rpt);
		else
			ccw_req = dasd_eckd_build_check(base, fdata, enable_pav,
							fmt_buffer, rpt);
	}

	return ccw_req;
}