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
struct vhost_scsi_cmd {int dummy; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* sg_page (int /*<<< orphan*/ ) ; 
 int vhost_scsi_map_to_sgl (struct vhost_scsi_cmd*,struct iov_iter*,struct scatterlist*,int) ; 

__attribute__((used)) static int
vhost_scsi_iov_to_sgl(struct vhost_scsi_cmd *cmd, bool write,
		      struct iov_iter *iter,
		      struct scatterlist *sg, int sg_count)
{
	struct scatterlist *p = sg;
	int ret;

	while (iov_iter_count(iter)) {
		ret = vhost_scsi_map_to_sgl(cmd, iter, sg, write);
		if (ret < 0) {
			while (p < sg) {
				struct page *page = sg_page(p++);
				if (page)
					put_page(page);
			}
			return ret;
		}
		sg += ret;
	}
	return 0;
}