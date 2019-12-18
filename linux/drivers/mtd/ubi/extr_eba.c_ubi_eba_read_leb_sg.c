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
struct ubi_volume {int dummy; } ;
struct ubi_sgl {size_t list_pos; int page_pos; struct scatterlist* sg; } ;
struct ubi_device {int dummy; } ;
struct scatterlist {int length; } ;

/* Variables and functions */
 size_t UBI_MAX_SG_COUNT ; 
 int sg_virt (struct scatterlist*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_eba_read_leb (struct ubi_device*,struct ubi_volume*,int,int,int,int,int) ; 

int ubi_eba_read_leb_sg(struct ubi_device *ubi, struct ubi_volume *vol,
			struct ubi_sgl *sgl, int lnum, int offset, int len,
			int check)
{
	int to_read;
	int ret;
	struct scatterlist *sg;

	for (;;) {
		ubi_assert(sgl->list_pos < UBI_MAX_SG_COUNT);
		sg = &sgl->sg[sgl->list_pos];
		if (len < sg->length - sgl->page_pos)
			to_read = len;
		else
			to_read = sg->length - sgl->page_pos;

		ret = ubi_eba_read_leb(ubi, vol, lnum,
				       sg_virt(sg) + sgl->page_pos, offset,
				       to_read, check);
		if (ret < 0)
			return ret;

		offset += to_read;
		len -= to_read;
		if (!len) {
			sgl->page_pos += to_read;
			if (sgl->page_pos == sg->length) {
				sgl->list_pos++;
				sgl->page_pos = 0;
			}

			break;
		}

		sgl->list_pos++;
		sgl->page_pos = 0;
	}

	return ret;
}