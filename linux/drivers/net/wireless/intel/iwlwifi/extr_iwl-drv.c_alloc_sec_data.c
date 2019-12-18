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
struct iwl_firmware_pieces {struct fw_img_parsing* img; } ;
struct fw_sec {int dummy; } ;
struct fw_img_parsing {int sec_counter; struct fw_sec* sec; } ;
typedef  enum iwl_ucode_type { ____Placeholder_iwl_ucode_type } iwl_ucode_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct fw_sec* krealloc (struct fw_sec*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alloc_sec_data(struct iwl_firmware_pieces *pieces,
			   enum iwl_ucode_type type,
			   int sec)
{
	struct fw_img_parsing *img = &pieces->img[type];
	struct fw_sec *sec_memory;
	int size = sec + 1;
	size_t alloc_size = sizeof(*img->sec) * size;

	if (img->sec && img->sec_counter >= size)
		return;

	sec_memory = krealloc(img->sec, alloc_size, GFP_KERNEL);
	if (!sec_memory)
		return;

	img->sec = sec_memory;
	img->sec_counter = size;
}