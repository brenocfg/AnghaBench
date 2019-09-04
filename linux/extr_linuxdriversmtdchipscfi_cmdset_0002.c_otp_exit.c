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
struct map_info {struct cfi_private* fldrv_priv; } ;
struct flchip {scalar_t__ start; } ;
struct cfi_private {int /*<<< orphan*/  device_type; int /*<<< orphan*/  addr_unlock1; int /*<<< orphan*/  addr_unlock2; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALIDATE_CACHED_RANGE (struct map_info*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  cfi_send_gen_cmd (int,int /*<<< orphan*/ ,scalar_t__,struct map_info*,struct cfi_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void otp_exit(struct map_info *map, struct flchip *chip,
			    loff_t adr, size_t len)
{
	struct cfi_private *cfi = map->fldrv_priv;

	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, NULL);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, NULL);
	cfi_send_gen_cmd(0x90, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, NULL);
	cfi_send_gen_cmd(0x00, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, NULL);

	INVALIDATE_CACHED_RANGE(map, chip->start + adr, len);
}