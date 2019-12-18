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
typedef  int u64 ;
struct msm_mdss {int dummy; } ;
struct dpu_mdss {int num_paths; int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int MAX_BW ; 
 int /*<<< orphan*/  icc_set_bw (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kBps_to_icc (int) ; 
 struct dpu_mdss* to_dpu_mdss (struct msm_mdss*) ; 

__attribute__((used)) static void dpu_mdss_icc_request_bw(struct msm_mdss *mdss)
{
	struct dpu_mdss *dpu_mdss = to_dpu_mdss(mdss);
	int i;
	u64 avg_bw = dpu_mdss->num_paths ? MAX_BW / dpu_mdss->num_paths : 0;

	for (i = 0; i < dpu_mdss->num_paths; i++)
		icc_set_bw(dpu_mdss->path[i], avg_bw, kBps_to_icc(MAX_BW));
}