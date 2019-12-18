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
typedef  int /*<<< orphan*/  u64 ;
struct ba_lun_info {int /*<<< orphan*/  free_aun_cnt; } ;
struct ba_lun {struct ba_lun_info* ba_lun_handle; } ;

/* Variables and functions */

__attribute__((used)) static u64 ba_space(struct ba_lun *ba_lun)
{
	struct ba_lun_info *bali = ba_lun->ba_lun_handle;

	return bali->free_aun_cnt;
}