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
struct loop_info64 {scalar_t__ lo_device; scalar_t__ lo_inode; scalar_t__ lo_rdevice; scalar_t__ lo_offset; scalar_t__ lo_encrypt_type; int /*<<< orphan*/  lo_encrypt_key; int /*<<< orphan*/  lo_file_name; int /*<<< orphan*/  lo_crypt_name; int /*<<< orphan*/ * lo_init; int /*<<< orphan*/  lo_flags; int /*<<< orphan*/  lo_encrypt_key_size; int /*<<< orphan*/  lo_number; } ;
struct loop_info {scalar_t__ lo_device; scalar_t__ lo_inode; scalar_t__ lo_rdevice; scalar_t__ lo_offset; scalar_t__ lo_encrypt_type; int /*<<< orphan*/  lo_encrypt_key; int /*<<< orphan*/  lo_name; int /*<<< orphan*/ * lo_init; int /*<<< orphan*/  lo_flags; int /*<<< orphan*/  lo_encrypt_key_size; int /*<<< orphan*/  lo_number; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 scalar_t__ LO_CRYPT_CRYPTOAPI ; 
 int /*<<< orphan*/  LO_KEY_SIZE ; 
 int /*<<< orphan*/  LO_NAME_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct loop_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
loop_info64_to_old(const struct loop_info64 *info64, struct loop_info *info)
{
	memset(info, 0, sizeof(*info));
	info->lo_number = info64->lo_number;
	info->lo_device = info64->lo_device;
	info->lo_inode = info64->lo_inode;
	info->lo_rdevice = info64->lo_rdevice;
	info->lo_offset = info64->lo_offset;
	info->lo_encrypt_type = info64->lo_encrypt_type;
	info->lo_encrypt_key_size = info64->lo_encrypt_key_size;
	info->lo_flags = info64->lo_flags;
	info->lo_init[0] = info64->lo_init[0];
	info->lo_init[1] = info64->lo_init[1];
	if (info->lo_encrypt_type == LO_CRYPT_CRYPTOAPI)
		memcpy(info->lo_name, info64->lo_crypt_name, LO_NAME_SIZE);
	else
		memcpy(info->lo_name, info64->lo_file_name, LO_NAME_SIZE);
	memcpy(info->lo_encrypt_key, info64->lo_encrypt_key, LO_KEY_SIZE);

	/* error in case values were truncated */
	if (info->lo_device != info64->lo_device ||
	    info->lo_rdevice != info64->lo_rdevice ||
	    info->lo_inode != info64->lo_inode ||
	    info->lo_offset != info64->lo_offset)
		return -EOVERFLOW;

	return 0;
}