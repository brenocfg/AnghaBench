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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i1480 {int /*<<< orphan*/  dev; } ;
struct fw_hdr {struct fw_hdr* next; scalar_t__ length; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int fw_hdr_load (struct i1480*,struct fw_hdr*,unsigned int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_hdrs_free (struct fw_hdr*) ; 
 int /*<<< orphan*/  kfree (struct fw_hdr*) ; 
 struct fw_hdr* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int fw_hdrs_load(struct i1480 *i1480, struct fw_hdr **phdr,
		 const char *_data, size_t data_size)
{
	int result;
	unsigned hdr_cnt = 0;
	u32 *data = (u32 *) _data, *data_itr, *data_top;
	struct fw_hdr *hdr, **prev_hdr = phdr;

	result = -EINVAL;
	/* Check size is ok and pointer is aligned */
	if (data_size % sizeof(u32) != 0)
		goto error;
	if ((unsigned long) _data % sizeof(u16) != 0)
		goto error;
	*phdr = NULL;
	data_itr = data;
	data_top = (u32 *) (_data + data_size);
	while (data_itr < data_top) {
		result = -ENOMEM;
		hdr = kmalloc(sizeof(*hdr), GFP_KERNEL);
		if (hdr == NULL) {
			dev_err(i1480->dev, "Cannot allocate fw header "
			       "for chunk #%u\n", hdr_cnt);
			goto error_alloc;
		}
		result = fw_hdr_load(i1480, hdr, hdr_cnt,
				     _data, data_itr, data_top);
		if (result < 0)
			goto error_load;
		data_itr += 2 + hdr->length;
		*prev_hdr = hdr;
		prev_hdr = &hdr->next;
		hdr_cnt++;
	};
	*prev_hdr = NULL;
	return 0;

error_load:
	kfree(hdr);
error_alloc:
	fw_hdrs_free(*phdr);
error:
	return result;
}