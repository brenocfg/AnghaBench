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
struct ptp_clock_request {int type; } ;
struct ptp_clock_info {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  PTP_CLK_REQ_EXTTS 130 
#define  PTP_CLK_REQ_PEROUT 129 
#define  PTP_CLK_REQ_PPS 128 
 int mlx5_extts_configure (struct ptp_clock_info*,struct ptp_clock_request*,int) ; 
 int mlx5_perout_configure (struct ptp_clock_info*,struct ptp_clock_request*,int) ; 
 int mlx5_pps_configure (struct ptp_clock_info*,struct ptp_clock_request*,int) ; 

__attribute__((used)) static int mlx5_ptp_enable(struct ptp_clock_info *ptp,
			   struct ptp_clock_request *rq,
			   int on)
{
	switch (rq->type) {
	case PTP_CLK_REQ_EXTTS:
		return mlx5_extts_configure(ptp, rq, on);
	case PTP_CLK_REQ_PEROUT:
		return mlx5_perout_configure(ptp, rq, on);
	case PTP_CLK_REQ_PPS:
		return mlx5_pps_configure(ptp, rq, on);
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}