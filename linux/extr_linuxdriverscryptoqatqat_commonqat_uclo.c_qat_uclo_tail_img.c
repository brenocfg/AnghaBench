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
struct icp_qat_suof_img_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct icp_qat_suof_img_hdr*,struct icp_qat_suof_img_hdr*,int) ; 

__attribute__((used)) static void qat_uclo_tail_img(struct icp_qat_suof_img_hdr *suof_img_hdr,
			      unsigned int img_id, unsigned int num_simgs)
{
	struct icp_qat_suof_img_hdr img_header;

	if (img_id != num_simgs - 1) {
		memcpy(&img_header, &suof_img_hdr[num_simgs - 1],
		       sizeof(*suof_img_hdr));
		memcpy(&suof_img_hdr[num_simgs - 1], &suof_img_hdr[img_id],
		       sizeof(*suof_img_hdr));
		memcpy(&suof_img_hdr[img_id], &img_header,
		       sizeof(*suof_img_hdr));
	}
}