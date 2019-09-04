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
struct firmware {scalar_t__ size; scalar_t__ data; } ;
struct common_firmware_header {int /*<<< orphan*/  size_bytes; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

int radeon_ucode_validate(const struct firmware *fw)
{
	const struct common_firmware_header *hdr =
		(const struct common_firmware_header *)fw->data;

	if (fw->size == le32_to_cpu(hdr->size_bytes))
		return 0;

	return -EINVAL;
}