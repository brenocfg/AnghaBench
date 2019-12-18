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
struct ras_err_handler_data {unsigned int count; unsigned int space_left; void* bps; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static int amdgpu_ras_realloc_eh_data_space(struct amdgpu_device *adev,
		struct ras_err_handler_data *data, int pages)
{
	unsigned int old_space = data->count + data->space_left;
	unsigned int new_space = old_space + pages;
	unsigned int align_space = ALIGN(new_space, 1024);
	void *tmp = kmalloc(align_space * sizeof(*data->bps), GFP_KERNEL);

	if (!tmp)
		return -ENOMEM;

	if (data->bps) {
		memcpy(tmp, data->bps,
				data->count * sizeof(*data->bps));
		kfree(data->bps);
	}

	data->bps = tmp;
	data->space_left += align_space - old_space;
	return 0;
}