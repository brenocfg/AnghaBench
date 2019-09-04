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
typedef  unsigned int u32 ;
struct scatterlist {int length; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,unsigned int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ sg_page (struct scatterlist*) ; 

__attribute__((used)) static unsigned int cc_get_sgl_nents(struct device *dev,
				     struct scatterlist *sg_list,
				     unsigned int nbytes, u32 *lbytes,
				     bool *is_chained)
{
	unsigned int nents = 0;

	while (nbytes && sg_list) {
		if (sg_list->length) {
			nents++;
			/* get the number of bytes in the last entry */
			*lbytes = nbytes;
			nbytes -= (sg_list->length > nbytes) ?
					nbytes : sg_list->length;
			sg_list = sg_next(sg_list);
		} else {
			sg_list = (struct scatterlist *)sg_page(sg_list);
			if (is_chained)
				*is_chained = true;
		}
	}
	dev_dbg(dev, "nents %d last bytes %d\n", nents, *lbytes);
	return nents;
}