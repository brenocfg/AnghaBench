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
typedef  int /*<<< orphan*/  u8 ;
struct firmware {size_t size; int /*<<< orphan*/  data; } ;
struct ath6kl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_get_fw(struct ath6kl *ar, const char *filename,
			 u8 **fw, size_t *fw_len)
{
	const struct firmware *fw_entry;
	int ret;

	ret = request_firmware(&fw_entry, filename, ar->dev);
	if (ret)
		return ret;

	*fw_len = fw_entry->size;
	*fw = kmemdup(fw_entry->data, fw_entry->size, GFP_KERNEL);

	if (*fw == NULL)
		ret = -ENOMEM;

	release_firmware(fw_entry);

	return ret;
}