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
struct loop_info64 {scalar_t__ lo_encrypt_type; int /*<<< orphan*/  lo_encrypt_key; int /*<<< orphan*/  lo_file_name; int /*<<< orphan*/  lo_crypt_name; int /*<<< orphan*/ * lo_init; int /*<<< orphan*/  lo_flags; int /*<<< orphan*/  lo_encrypt_key_size; scalar_t__ lo_sizelimit; int /*<<< orphan*/  lo_offset; int /*<<< orphan*/  lo_rdevice; int /*<<< orphan*/  lo_inode; int /*<<< orphan*/  lo_device; int /*<<< orphan*/  lo_number; } ;
struct loop_info {scalar_t__ lo_encrypt_type; int /*<<< orphan*/  lo_encrypt_key; int /*<<< orphan*/  lo_name; int /*<<< orphan*/ * lo_init; int /*<<< orphan*/  lo_flags; int /*<<< orphan*/  lo_encrypt_key_size; int /*<<< orphan*/  lo_offset; int /*<<< orphan*/  lo_rdevice; int /*<<< orphan*/  lo_inode; int /*<<< orphan*/  lo_device; int /*<<< orphan*/  lo_number; } ;

/* Variables and functions */
 scalar_t__ LO_CRYPT_CRYPTOAPI ; 
 int /*<<< orphan*/  LO_KEY_SIZE ; 
 int /*<<< orphan*/  LO_NAME_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct loop_info64*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
loop_info64_from_old(const struct loop_info *info, struct loop_info64 *info64)
{
	memset(info64, 0, sizeof(*info64));
	info64->lo_number = info->lo_number;
	info64->lo_device = info->lo_device;
	info64->lo_inode = info->lo_inode;
	info64->lo_rdevice = info->lo_rdevice;
	info64->lo_offset = info->lo_offset;
	info64->lo_sizelimit = 0;
	info64->lo_encrypt_type = info->lo_encrypt_type;
	info64->lo_encrypt_key_size = info->lo_encrypt_key_size;
	info64->lo_flags = info->lo_flags;
	info64->lo_init[0] = info->lo_init[0];
	info64->lo_init[1] = info->lo_init[1];
	if (info->lo_encrypt_type == LO_CRYPT_CRYPTOAPI)
		memcpy(info64->lo_crypt_name, info->lo_name, LO_NAME_SIZE);
	else
		memcpy(info64->lo_file_name, info->lo_name, LO_NAME_SIZE);
	memcpy(info64->lo_encrypt_key, info->lo_encrypt_key, LO_KEY_SIZE);
}